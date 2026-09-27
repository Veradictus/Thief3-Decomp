extends Node3D

## Map viewer: shows the map scene the picker loaded, with a fly camera, a HUD,
## a help overlay, view modes, lighting modes, light and marker toggles, and an
## actor inspector (click or I).  Esc releases the mouse, then returns to the
## map list.  See help_overlay.gd for the full list of controls.

# =============================================================================
# VARIABLES
# =============================================================================

## The fly camera.
var camera: FlyCamera

## The root of the currently loaded map scene.
var map_root: Node3D

## The picking helper, indexed over `map_root`'s meshes and markers.
var picker := Pick.new()

## Gizmos for `map_root`'s geometry-less actors.
var gizmos := Gizmos.new()

## Current View value.
var view_mode: int = View.LIT

## Every light in the map, for set_lights().
var lights: Array[Light3D] = []

## Whether the map's own lights are on.
var lights_on := true

## Current Lighting value.
var lighting: int = Lighting.EDITOR

## Whether gizmo markers are shown.
var markers_on := true

## Unreal units per metre, from the map's t3_units_per_meter metadata.
var units_per_meter := 16.0 / 0.3048

## Every PlayerStart marker in the map, for go_to_start().
var starts: Array[Node3D] = []

## Index into `starts` of the last player start the camera went to.
var start_index := -1

## The current T3Meta.describe() result for the picked/inspected object.
var selected: Dictionary = {}

## The map entry being viewed (T3Viewer.current).
var _entry: Dictionary = {}

## The map's display title.
var _title := ''

## The single WorldEnvironment node, switched between the level's own
## environment and the flat preview one.
var _world_env: WorldEnvironment

## The flat, bright preview environment (FLAT lighting, or a map with none of its own).
var _preview_env: Environment

## The map's own environment, if it has one.
var _level_env: Environment

## The editor-style preview sun, shown only in EDITOR lighting.
var _sun: DirectionalLight3D

## The HUD overlay.
var _hud: Hud

## The controls-reference overlay.
var _help: Help

## The actor inspector side panel.
var _inspector: Inspector

## The selection outline box.
var _selection: SelectionBox

## Status text shown while the map is still building ("Building <map>…").
var _status: Label

## Whether _ready() has finished setting up the map (see is_ready()).
var _ready_flag := false

## Seconds until the HUD info text is next refreshed.
var _hud_timer := 0.0

# =============================================================================
# CONSTANTS
# =============================================================================

## The fly camera script.
const FlyCamera := preload('res://t3_tools/viewer/fly_camera.gd')

## The HUD overlay script.
const Hud := preload('res://t3_tools/viewer/hud.gd')

## The controls-reference overlay script.
const Help := preload('res://t3_tools/viewer/help_overlay.gd')

## The actor inspector side panel script.
const Inspector := preload('res://t3_tools/viewer/actor_inspector.gd')

## The ray-picking helper script.
const Pick := preload('res://t3_tools/viewer/t3_pick.gd')

## The T3 node-metadata reader script.
const Meta := preload('res://t3_tools/viewer/t3_meta.gd')

## The gizmo-building script, for actors without geometry of their own.
const Gizmos := preload('res://t3_tools/viewer/marker_gizmos.gd')

## The selection outline box script.
const SelectionBox := preload('res://t3_tools/viewer/selection_box.gd')

## The shared UI theme and style helpers.
const UiTheme := preload('res://t3_tools/viewer/theme.gd')

## The three view (debug draw) modes, cycled with V.
enum View { LIT, UNLIT, WIREFRAME }

## Display names for View, in order.
const VIEW_NAMES := ['lit', 'unlit', 'wireframe']

## Viewport debug-draw mode for each View value.
const VIEW_DRAW := [Viewport.DEBUG_DRAW_DISABLED, Viewport.DEBUG_DRAW_UNSHADED, Viewport.DEBUG_DRAW_WIREFRAME]

## Metres above a player start's origin the camera is placed at.
const EYE_HEIGHT := 0.6

## Lighting modes, cycled with K.  EDITOR looks like the map scene opened in
## the Godot editor: the level's own environment plus the editor's preview sun,
## which the editor adds to every scene without a DirectionalLight3D (all T3
## maps).  GAME is the level's environment and lamps only, as in T3 itself,
## which has no sun.  FLAT is an even, bright light for dark corners.
enum Lighting { EDITOR, GAME, FLAT }

## Display names for Lighting, in order.
const LIGHTING_NAMES := ['editor', 'game', 'flat']

## Toast text shown when switching to each Lighting mode.
const LIGHTING_TOASTS := [
	'Lighting: editor (level fog and ambient, lamps, preview sun)',
	'Lighting: game (level fog and ambient, lamps only)',
	'Lighting: flat (even preview light)',
]

## The editor's default preview sun (Node3DEditor::_load_default_preview_settings):
## altitude 60 degrees, azimuth 150 degrees, white, energy 1, four shadow
## splits out to 100 m.
const SUN_ROTATION_DEG := Vector3(-60.0, 150.0, 0.0)

## Shadow draw distance for the preview sun, in metres.
const SUN_SHADOW_MAX_DISTANCE := 100.0

# =============================================================================
# METHODS
# =============================================================================

## Takes the pending scene from the picker, instantiates it, and builds the
## map (camera, lights, gizmos, environment).
func _ready() -> void:
	_entry = T3Viewer.current
	_title = T3Viewer.map_title(_entry)
	build_ui()

	var packed := T3Viewer.take_pending_scene()
	if packed == null:
		_status.text = 'No map was loaded. Returning to the map list…'
		await get_tree().create_timer(1.5).timeout
		T3Viewer.back_to_picker()
		return

	_status.text = 'Building %s…' % _title

	# Let the status label actually draw before instantiate() blocks the main thread.
	await get_tree().process_frame
	await get_tree().process_frame

	map_root = packed.instantiate() as Node3D
	if map_root == null:
		_status.text = 'The map scene could not be instantiated.'
		return

	add_child(map_root)
	setup_map()
	_status.visible = false
	_ready_flag = true
	apply_command_line()

## Whether _ready() has finished setting up the map.
func is_ready() -> bool:
	return _ready_flag

# --- Setup ---

## Builds the HUD, inspector, help overlay and the status label.
func build_ui() -> void:
	var layer := CanvasLayer.new()
	add_child(layer)
	var root := Control.new()
	root.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
	root.mouse_filter = Control.MOUSE_FILTER_IGNORE
	root.theme = UiTheme.build()
	layer.add_child(root)

	_hud = Hud.new()
	root.add_child(_hud)

	_inspector = Inspector.new()
	_inspector.anchor_left = 1.0
	_inspector.anchor_right = 1.0
	_inspector.anchor_top = 0.0
	_inspector.anchor_bottom = 1.0
	_inspector.offset_left = -424
	_inspector.offset_right = -12
	_inspector.offset_top = 12
	_inspector.offset_bottom = -12
	_inspector.focus_requested.connect(focus_selection)
	_inspector.closed.connect(clear_selection)
	root.add_child(_inspector)

	_help = Help.new()
	root.add_child(_help)

	_status = UiTheme.label('', 22)
	_status.set_anchors_and_offsets_preset(Control.PRESET_CENTER)
	_status.grow_horizontal = Control.GROW_DIRECTION_BOTH
	_status.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	root.add_child(_status)

## Reads the map's scale metadata, sets up lighting, indexes meshes and gizmos
## for picking, finds player starts, creates the camera and selection box, and
## places the camera at the default start (or an overview).
func setup_map() -> void:
	units_per_meter = float(map_root.get_meta('t3_units_per_meter', units_per_meter))

	# One WorldEnvironment at a time: the viewer's own, showing either the
	# level's environment (ambient + fog, unchanged) or the flat preview one.
	_preview_env = make_preview_environment()
	for we in map_root.find_children('*', 'WorldEnvironment', true, false):
		# Keep the first one found; a map should have at most one.
		if _level_env == null:
			_level_env = (we as WorldEnvironment).environment
		we.get_parent().remove_child(we)
		we.queue_free()
	_world_env = WorldEnvironment.new()
	add_child(_world_env)
	_sun = make_preview_sun()
	add_child(_sun)
	apply_lighting()

	for l in map_root.find_children('*', 'Light3D', true, false):
		lights.append(l)

	picker.index_meshes(map_root)
	gizmos.build(map_root)
	picker.markers = gizmos.targets

	for n in map_root.find_children('*', 'Marker3D', true, false):
		if String(n.get_meta('t3_class', '')) == 'PlayerStart':
			starts.append(n)
	starts.sort_custom(default_start_sorts_first)

	camera = FlyCamera.new()
	camera.name = 'FlyCamera'
	camera.fov = 75.0
	camera.near = 0.05
	camera.far = 4000.0
	add_child(camera)
	camera.current = true
	camera.speed_changed.connect(func(s): _hud.toast('Base speed %.1f m/s' % s))
	_selection = SelectionBox.new()
	add_child(_selection)

	if not go_to_start(0, false):
		go_to_overview()
	get_window().title = '%s - %s' % [T3Viewer.APP_TITLE, _title]
	update_hud()

## Comparator for starts.sort_custom(): the default start (if any) sorts first.
func default_start_sorts_first(a: Node, b: Node) -> bool:
	return bool(a.get_meta('t3_default_start', false)) and not bool(b.get_meta('t3_default_start', false))

## A flat, bright environment for FLAT lighting, or for a map with no
## environment of its own.
func make_preview_environment() -> Environment:
	var env := Environment.new()
	env.background_mode = Environment.BG_COLOR
	env.background_color = Color(0.09, 0.1, 0.13)
	env.ambient_light_source = Environment.AMBIENT_SOURCE_COLOR
	env.ambient_light_color = Color(1, 1, 1)
	env.ambient_light_energy = 0.55
	env.tonemap_mode = Environment.TONE_MAPPER_FILMIC
	return env

## A copy of the Godot editor's default preview sun, so the EDITOR lighting
## mode matches what the editor shows.
func make_preview_sun() -> DirectionalLight3D:
	var sun := DirectionalLight3D.new()
	sun.name = 'PreviewSun'
	sun.rotation_degrees = SUN_ROTATION_DEG
	sun.shadow_enabled = true
	sun.directional_shadow_mode = DirectionalLight3D.SHADOW_PARALLEL_4_SPLITS
	sun.directional_shadow_max_distance = SUN_SHADOW_MAX_DISTANCE
	return sun

## Shows either the level's own environment or the flat preview one, and the
## preview sun only in EDITOR lighting.
func apply_lighting() -> void:
	# A map without environment settings falls back to the preview light.
	var level_env := lighting != Lighting.FLAT and _level_env != null
	_world_env.environment = _level_env if level_env else _preview_env
	_sun.visible = lighting == Lighting.EDITOR

# --- Camera Placement ---

## Moves the camera to player start `index` (wrapped), or returns false if the
## map has none. Announces the destination via a HUD toast unless `announce`
## is false.
func go_to_start(index: int, announce: bool = true) -> bool:
	if starts.is_empty():
		return false

	start_index = posmod(index, starts.size())
	var s := starts[start_index]
	var xf := s.global_transform

	# The exporter maps Unreal +X (forward) to Godot +X.
	var fwd := xf.basis.x
	fwd.y = 0.0

	# The start faces straight up or down; look forward instead.
	if fwd.length_squared() < 1e-6:
		fwd = Vector3.FORWARD

	var pos := xf.origin + Vector3.UP * EYE_HEIGHT
	camera.look_from(pos, pos + fwd.normalized())

	if announce:
		var dest := ''
		var gs = Meta.json(s, 't3_gamesys')
		if gs is Dictionary and gs.has('TeleportDestName'):
			dest = ' (%s)' % gs['TeleportDestName']
		_hud.toast('Player start %d of %d%s' % [start_index + 1, starts.size(), dest])

	return true

## Frames the camera on the whole map's bounds, for maps with no player start.
func go_to_overview() -> void:
	var box := picker.world_bounds()
	var c := box.get_center()
	var r := maxf(box.size.length() * 0.5, 5.0)
	camera.look_from(c + Vector3(r * 0.45, r * 0.55, r * 0.45), c)

## Tweens the camera to frame the current selection, keeping its current look direction.
func focus_selection() -> void:
	var t = selected.get('target')
	if not (t is Node3D) or not is_instance_valid(t):
		_hud.toast('Nothing selected')
		return

	var n3 := t as Node3D
	var box := Pick.local_bounds(n3)
	var center: Vector3 = n3.global_transform * box.get_center()
	var radius := maxf((n3.global_transform.basis * box.size).length() * 0.5, 0.3)
	var dir := -camera.global_transform.basis.z
	var dest := center - dir * (radius * 2.2 + 0.6)
	var from := camera.global_position

	var tw := create_tween()
	var step := tw.tween_method(func(k: float): camera.look_from(from.lerp(dest, k), center), 0.0, 1.0, 0.35)
	step.set_trans(Tween.TRANS_CUBIC)
	step.set_ease(Tween.EASE_OUT)

# --- Modes ---

## Sets the debug-draw view mode and shows a HUD toast.
func set_view_mode(mode: int) -> void:
	view_mode = clampi(mode, 0, VIEW_NAMES.size() - 1)
	get_viewport().debug_draw = VIEW_DRAW[view_mode]
	_hud.toast('View: ' + VIEW_NAMES[view_mode])

## Display name of the current view mode.
func view_mode_name() -> String:
	return VIEW_NAMES[view_mode]

## Turns the map's own lights on or off.
func set_lights(on: bool) -> void:
	lights_on = on
	for l in lights:
		if is_instance_valid(l):
			l.visible = on
	_hud.toast('Lamps ' + ('on' if on else 'off'))

## Sets the Lighting mode (wrapped) and shows a HUD toast, warning if the map
## has no environment of its own.
func set_lighting(mode: int) -> void:
	lighting = posmod(mode, LIGHTING_NAMES.size())
	apply_lighting()
	if lighting != Lighting.FLAT and _level_env == null:
		_hud.toast(LIGHTING_TOASTS[lighting] + ' - this map has no fog / ambient settings')
	else:
		_hud.toast(LIGHTING_TOASTS[lighting])

## Shows or hides the geometry-less actors' gizmos.
func set_markers(on: bool) -> void:
	markers_on = on
	gizmos.set_visible(on)
	_hud.toast('Markers ' + ('shown' if on else 'hidden'))

# --- Inspection ---

## Picks at `screen_pos` and shows the hit in the inspector, or toasts
## "Nothing there" and clears the selection on a miss.
func inspect_at(screen_pos: Vector2) -> Dictionary:
	var hit := picker.pick(camera, screen_pos, markers_on)
	if hit.is_empty():
		clear_selection()
		_hud.toast('Nothing there')
		return {}

	return select(hit)

## Picks at the centre of the viewport (the crosshair).
func inspect_at_screen_center() -> Dictionary:
	return inspect_at(get_viewport().get_visible_rect().size * 0.5)

## Selects the first mesh actor of the map, or else the first marker (used by
## the self-test).
func inspect_first_actor() -> Dictionary:
	for mi in picker.meshes:
		if is_instance_valid(mi) and mi.is_visible_in_tree() and Meta.actor_node(mi) != null:
			return select({'node': mi, 'position': mi.global_position, 'distance': 0.0, 'kind': 'mesh', 'surface': 0})

	for m in picker.markers:
		if is_instance_valid(m):
			return select({'node': m, 'position': m.global_position, 'distance': 0.0, 'kind': 'marker'})

	return {}

## Records `hit` as the current selection and updates the inspector and the
## selection box.
func select(hit: Dictionary) -> Dictionary:
	var info := Meta.describe(hit, units_per_meter)
	selected = info
	_inspector.show_info(info)
	var target = info.get('target')
	_selection.show_for(target if target is Node3D else null)
	return info

## Clears the current selection and hides the inspector and selection box.
func clear_selection() -> void:
	selected = {}
	_inspector.clear()
	_selection.hide_box()

## Where to aim a pick: the crosshair while looking, else the mouse position
## (or `event`'s, for a click).
func aim_point(event: InputEvent = null) -> Vector2:
	if camera.is_looking():
		return get_viewport().get_visible_rect().size * 0.5

	if event is InputEventMouse:
		return (event as InputEventMouse).position

	return get_viewport().get_mouse_position()

# --- Leaving ---

## Resets the debug-draw view, releases the mouse, and returns to the picker.
func leave() -> void:
	get_viewport().debug_draw = Viewport.DEBUG_DRAW_DISABLED
	camera.set_captured(false)
	T3Viewer.back_to_picker()

# --- HUD ---

## Rebuilds the HUD's multi-line info text (map, FPS, position, speed, modes, selection).
func update_hud() -> void:
	var fc := camera
	var p := camera.global_position
	var uu := Meta.to_unreal(p, units_per_meter)
	var lines: Array[String] = []
	lines.append('%s   [%s]' % [_title, _entry.get('id', '')])
	lines.append('FPS %d   meshes %d   lights %d   markers %d' % [
		int(Engine.get_frames_per_second()), picker.meshes.size(), lights.size(), gizmos.targets.size()])
	lines.append('Pos %8.2f %8.2f %8.2f m   (UU %.0f, %.0f, %.0f)' % [p.x, p.y, p.z, uu.x, uu.y, uu.z])
	lines.append('Speed %.1f m/s   Shift %.1f   Alt %.1f   now %.1f' % [fc.base_speed, fc.base_speed * fc.fast_factor,
		fc.base_speed * fc.slow_factor, fc.velocity.length()])
	lines.append('View %s   lighting %s   lamps %s   markers %s' % [VIEW_NAMES[view_mode],
		LIGHTING_NAMES[lighting], 'on' if lights_on else 'off', 'on' if markers_on else 'off'])
	if not selected.is_empty():
		lines.append('Selected %s  (%s)' % [selected.get('title', ''), selected.get('subtitle', '')])

	_hud.set_info('\n'.join(lines))

# --- Scripted Use ---

## Indexed counts, for the self-test.
func stats() -> Dictionary:
	return {'meshes': picker.meshes.size(), 'markers': gizmos.targets.size(), 'lights': lights.size(),
		'starts': starts.size()}

## Applies --t3-camera/--t3-view/--t3-lighting/--t3-select/--t3-help, and saves
## a screenshot and quits if --t3-screenshot was given.
func apply_command_line() -> void:
	var o: Dictionary = T3Viewer.options
	if o.has('camera'):
		var c: Array = o['camera']
		camera.look_from(Vector3(c[0], c[1], c[2]), Vector3(c[3], c[4], c[5]))

	if o.has('view'):
		var m := VIEW_NAMES.find(String(o['view']))

		# Ignore an unrecognised name rather than erroring out.
		if m >= 0:
			set_view_mode(m)

	if o.has('lighting'):
		var mode := LIGHTING_NAMES.find(String(o['lighting']))

		# Ignore an unrecognised name rather than erroring out.
		if mode >= 0:
			set_lighting(mode)

	if o.has('select'):
		inspect_at_screen_center()

	if o.has('help'):
		_help.visible = true

	if o.has('screenshot') and not o.has('selftest'):
		var frames := int(o.get('frames', '30'))
		for i in frames:
			await get_tree().process_frame

		update_hud()
		await RenderingServer.frame_post_draw
		var img := get_viewport().get_texture().get_image()
		var path := String(o['screenshot'])
		var err := img.save_png(path)
		print('screenshot %s: %s' % [path, 'saved' if err == OK else 'error %d' % err])
		get_tree().quit(0 if err == OK else 1)

# --- Engine Callbacks ---

## Dispatches the t3_* input actions to the matching camera/mode/inspection method.
func _unhandled_input(event: InputEvent) -> void:
	if not _ready_flag:
		return

	if event.is_action_pressed('t3_back'):
		# Esc backs out one layer at a time: release the mouse, then close help, then leave.
		get_viewport().set_input_as_handled()
		if camera.captured:
			camera.set_captured(false)
		elif _help.visible:
			_help.visible = false
		else:
			leave.call_deferred()
		return
	elif event.is_action_pressed('t3_help'):
		_help.visible = not _help.visible
	elif event.is_action_pressed('t3_toggle_capture'):
		camera.set_captured(not camera.captured)
	elif event.is_action_pressed('t3_view_lit'):
		set_view_mode(View.LIT)
	elif event.is_action_pressed('t3_view_unlit'):
		set_view_mode(View.UNLIT)
	elif event.is_action_pressed('t3_view_wireframe'):
		set_view_mode(View.WIREFRAME)
	elif event.is_action_pressed('t3_view_cycle'):
		set_view_mode((view_mode + 1) % VIEW_NAMES.size())
	elif event.is_action_pressed('t3_toggle_lights'):
		set_lights(not lights_on)
	elif event.is_action_pressed('t3_cycle_lighting'):
		set_lighting(lighting + 1)
	elif event.is_action_pressed('t3_toggle_markers'):
		set_markers(not markers_on)
	elif event.is_action_pressed('t3_next_start'):
		if not go_to_start(start_index + 1):
			_hud.toast('This map has no player start')
	elif event.is_action_pressed('t3_focus'):
		focus_selection()
	elif event.is_action_pressed('t3_inspect'):
		inspect_at(aim_point())
	elif event.is_action_pressed('t3_select'):
		inspect_at(aim_point(event))
	else:
		return
	get_viewport().set_input_as_handled()

## Updates the crosshair and refreshes the HUD text a few times a second (not every frame).
func _process(delta: float) -> void:
	if not _ready_flag:
		return

	_hud.set_crosshair(camera.is_looking())

	_hud_timer -= delta
	if _hud_timer <= 0.0:
		_hud_timer = 0.2
		update_hud()
