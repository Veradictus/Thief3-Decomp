extends Node

## Autoload "T3Viewer": shared state and services of the T3 map viewer.
##
## - finds the exported maps (index file written by tools/assets/t3map.py,
##   plus a scan of res:// for <Map>/<Map>.tscn scenes);
## - hands the map loaded by the picker over to the viewer scene;
## - makes sure the input actions exist (they are defined in project.godot;
##   this is a fallback for edited or older projects);
## - command-line options after "--" for scripted use:
##     --t3-map <id>           load this map directly (skips the picker)
##     --t3-selftest           drive picker and viewer automatically, then quit
##                             with exit code 0 (pass) or 1 (fail); works headless
##     --t3-screenshot <png>   save a frame of the viewer and quit (needs a GPU)
##     --t3-camera x y z tx ty tz   camera position and target, in metres
##     --t3-view lit|unlit|wireframe, --t3-lighting editor|game|flat,
##     --t3-select (inspect the crosshair target),
##     --t3-help (show the help overlay), --t3-frames <n> (frames before the shot)

# =============================================================================
# VARIABLES
# =============================================================================

## Exported maps found in the project: [{id, title, scene, actors, ...}, ...].
var maps: Array = []

## The map entry currently being viewed.
var current: Dictionary = {}

## The scene the picker loaded, waiting for the viewer to take ownership.
var pending_scene: PackedScene = null

## The map picker's last filter text, restored when returning to it.
var last_filter := ''

## The id of the last map opened, used to preselect it in the picker.
var last_selected := ''

## Parsed command-line options (see parse_args()).
var options := {}

## Descriptions of failed self-test checks, printed at the end.
var selftest_failures: Array[String] = []

# =============================================================================
# CONSTANTS
# =============================================================================

## The map picker scene.
const PICKER_SCENE := 'res://t3_tools/viewer/map_picker.tscn'

## The map viewer scene.
const VIEWER_SCENE := 'res://t3_tools/viewer/map_viewer.tscn'

## The exported map index written by t3map.py.
const INDEX_PATH := 'res://t3_maps.json'

## Base window title; the viewer appends " - <map>" while showing one.
const APP_TITLE := 'T3 Map Viewer'

## Default bindings: action -> list of [kind, code].  kind "phys" = physical key
## (layout independent, for movement), "key" = key label (mnemonics), "mouse".
const DEFAULT_ACTIONS := {
	't3_move_forward': [['phys', KEY_W], ['key', KEY_UP]],
	't3_move_back': [['phys', KEY_S], ['key', KEY_DOWN]],
	't3_move_left': [['phys', KEY_A], ['key', KEY_LEFT]],
	't3_move_right': [['phys', KEY_D], ['key', KEY_RIGHT]],
	't3_move_down': [['phys', KEY_Q], ['key', KEY_CTRL], ['key', KEY_PAGEDOWN]],
	't3_move_up': [['phys', KEY_E], ['key', KEY_SPACE], ['key', KEY_PAGEUP]],
	't3_fast': [['key', KEY_SHIFT]],
	't3_slow': [['key', KEY_ALT]],
	't3_look': [['mouse', MOUSE_BUTTON_RIGHT]],
	't3_select': [['mouse', MOUSE_BUTTON_LEFT]],
	't3_toggle_capture': [['key', KEY_C]],
	't3_inspect': [['key', KEY_I]],
	't3_focus': [['key', KEY_F]],
	't3_next_start': [['key', KEY_P]],
	't3_view_lit': [['key', KEY_1]],
	't3_view_unlit': [['key', KEY_2]],
	't3_view_wireframe': [['key', KEY_3]],
	't3_view_cycle': [['key', KEY_V]],
	't3_toggle_lights': [['key', KEY_L]],
	't3_cycle_lighting': [['key', KEY_K]],
	't3_toggle_markers': [['key', KEY_M]],
	't3_help': [['key', KEY_F1], ['key', KEY_H]],
	't3_back': [['key', KEY_ESCAPE]],
}

# =============================================================================
# METHODS
# =============================================================================

## Enables wireframe generation for meshes created from this point on (the
## renderer only builds wireframe index buffers for meshes created after this
## call, so it has to run before anything else creates one).
func _init() -> void:
	RenderingServer.set_debug_generate_wireframes(true)

## Ensures the input actions exist, parses the command line, sets the window
## title, and kicks off the self-test if requested.
func _ready() -> void:
	ensure_actions()
	options = parse_args(OS.get_cmdline_user_args())
	get_window().title = APP_TITLE

	# Deferred so the picker's own _ready has already run.
	if options.has('selftest'):
		run_selftest.call_deferred()

# --- Maps ---

## Rebuilds `maps` from t3_maps.json plus any `<Map>/<Map>.tscn` scene found
## by scanning the project (for maps exported without an index).
func refresh_maps() -> Array:
	maps.clear()
	var seen := {}

	if FileAccess.file_exists(INDEX_PATH):
		var data = JSON.parse_string(FileAccess.get_file_as_string(INDEX_PATH))
		if data is Dictionary and data.get('maps') is Array:
			for e in data['maps']:
				# Skip stale entries whose scene no longer exists.
				if e is Dictionary and ResourceLoader.exists(String(e.get('scene', ''))):
					maps.append(e)
					seen[e['scene']] = true

	var dir := DirAccess.open('res://')
	if dir != null:
		for sub in dir.get_directories():
			var scene := 'res://%s/%s.tscn' % [sub, sub]

			# A map exported without (or before) an index entry.
			if not seen.has(scene) and ResourceLoader.exists(scene):
				maps.append({'id': sub, 'title': sub, 'scene': scene})

	maps.sort_custom(func(a, b): return String(a.get('title', '')).naturalnocasecmp_to(String(b.get('title', ''))) < 0)
	return maps

## The map entry with the given id (case-insensitive), or {} if not found.
func find_map(id: String) -> Dictionary:
	for e in maps:
		if String(e.get('id', '')).to_lower() == id.to_lower():
			return e

	return {}

## The entry's title, or its id if it has none.
func map_title(entry: Dictionary) -> String:
	var title := String(entry.get('title', ''))
	return title if title != '' else String(entry.get('id', '?'))

## Called by the picker once the map scene has loaded.
func open_viewer(entry: Dictionary, scene: PackedScene) -> void:
	current = entry
	pending_scene = scene
	last_selected = String(entry.get('id', ''))
	get_tree().change_scene_to_file(VIEWER_SCENE)

## The viewer takes ownership of the loaded scene (so it can be freed later).
func take_pending_scene() -> PackedScene:
	var s := pending_scene
	pending_scene = null
	return s

## Releases the mouse, restores the window title, and switches back to the picker.
func back_to_picker() -> void:
	pending_scene = null
	Input.mouse_mode = Input.MOUSE_MODE_VISIBLE
	get_window().title = APP_TITLE
	get_tree().change_scene_to_file(PICKER_SCENE)

# --- Input ---

## Adds the default t3_* input actions if the project doesn't already define
## them (e.g. an older or hand-edited project.godot).
func ensure_actions() -> void:
	for action in DEFAULT_ACTIONS:
		# Don't override bindings already customised in the project.
		if InputMap.has_action(action):
			continue

		InputMap.add_action(action, 0.2)
		for spec in DEFAULT_ACTIONS[action]:
			var ev: InputEvent
			match spec[0]:
				'phys':
					var k := InputEventKey.new()
					k.physical_keycode = spec[1]
					ev = k
				'key':
					var k := InputEventKey.new()
					k.keycode = spec[1]
					ev = k
				_:
					var m := InputEventMouseButton.new()
					m.button_index = spec[1]
					ev = m
			InputMap.action_add_event(action, ev)

## Readable key list of an action, e.g. 'W / Up'.
func action_keys(action: String) -> String:
	if not InputMap.has_action(action):
		return '?'

	var parts: Array[String] = []
	for ev in InputMap.action_get_events(action):
		# Tidy up Godot's verbose event names for the HUD and help overlay.
		var text := ev.as_text().replace(' - Physical', '').replace(' (Physical)', '')
		text = text.replace('Left Mouse Button', 'Left click').replace('Right Mouse Button', 'Right mouse')
		if not parts.has(text):
			parts.append(text)

	return ' / '.join(parts)

# --- Command Line ---

## Parses the `--t3-*` options after `--` into a dictionary keyed by the
## option name with the `t3-` prefix removed (see the class doc comment for
## the full list).
static func parse_args(args: PackedStringArray) -> Dictionary:
	var out := {}
	var i := 0

	while i < args.size():
		var a := args[i]
		match a:
			# Options that take one value.
			'--t3-map', '--t3-screenshot', '--t3-view', '--t3-lighting', '--t3-frames':
				if i + 1 < args.size():
					out[a.trim_prefix('--t3-')] = args[i + 1]
					i += 1
			# Six numbers: position then target.
			'--t3-camera':
				if i + 6 < args.size():
					var v: Array[float] = []
					for k in 6:
						v.append(float(args[i + 1 + k]))
					out['camera'] = v
					i += 6
			# Boolean flags.
			'--t3-selftest', '--t3-select', '--t3-help':
				out[a.trim_prefix('--t3-')] = true
		i += 1

	return out

# --- Automated Check ---

## Prints a pass/fail line for one self-test assertion and records failures.
func check(ok: bool, what: String) -> bool:
	print(('  ok    ' if ok else '  FAIL  ') + what)
	if not ok:
		selftest_failures.append(what)

	return ok

## Waits `n` process frames.
func frames(n: int) -> void:
	for i in n:
		await get_tree().process_frame

## Waits up to `timeout_s` seconds for `path` to become the current scene and
## report itself ready, or returns null on timeout.
func wait_for_scene(path: String, timeout_s: float) -> Node:
	var t0 := Time.get_ticks_msec()

	while Time.get_ticks_msec() - t0 < timeout_s * 1000.0:
		var cur := get_tree().current_scene
		if cur != null and cur.scene_file_path == path and cur.has_method('is_ready') and cur.is_ready():
			return cur
		await get_tree().process_frame

	return null

## Presses and releases `action` for one frame each, as if the player had
## tapped the key.
func send_action(action: String) -> void:
	var ev := InputEventAction.new()
	ev.action = action
	ev.pressed = true
	Input.parse_input_event(ev)
	await get_tree().process_frame

	var up := InputEventAction.new()
	up.action = action
	up.pressed = false
	Input.parse_input_event(up)
	await get_tree().process_frame

## Drives the picker and the viewer through a full pass (load a map, move the
## camera, cycle every mode, inspect an actor, focus, and return to the
## picker), then quits with exit code 0 (pass) or 1 (fail).
func run_selftest() -> void:
	print('T3 viewer self-test')
	var picker = await wait_for_scene(PICKER_SCENE, 30.0)
	if not check(picker != null, 'map picker scene is running'):
		get_tree().quit(1)
		return

	refresh_maps()
	check(maps.size() > 0, 'found %d exported maps' % maps.size())
	var entry := find_map(String(options.get('map', ''))) if options.has('map') else {}

	# No --t3-map given (or not found): just use the first map.
	if entry.is_empty() and maps.size() > 0:
		entry = maps[0]
	if entry.is_empty():
		get_tree().quit(1)
		return

	print('  map: %s (%s)' % [map_title(entry), entry.get('id', '')])
	picker.start_load(entry)
	var viewer = await wait_for_scene(VIEWER_SCENE, 600.0)
	if not check(viewer != null, 'map loaded in the background and the viewer started'):
		get_tree().quit(1)
		return

	var stats: Dictionary = viewer.stats()
	check(int(stats.get('meshes', 0)) > 0, 'viewer indexed %d mesh instances, %d markers, %d lights' % [
		stats.get('meshes', 0), stats.get('markers', 0), stats.get('lights', 0)])

	var cam: Camera3D = viewer.camera
	var p0 := cam.global_position
	Input.action_press('t3_move_forward')
	Input.action_press('t3_fast')
	await frames(20)
	Input.action_release('t3_move_forward')
	Input.action_release('t3_fast')
	await frames(20)
	var moved := cam.global_position.distance_to(p0)
	check(moved > 0.05, 'camera moves with the forward action (%.2f m)' % moved)

	# Exercise every toggle twice, to land back where it started.
	for action in ['t3_view_unlit', 't3_view_wireframe', 't3_view_lit', 't3_toggle_lights', 't3_toggle_lights',
			't3_cycle_lighting', 't3_cycle_lighting', 't3_cycle_lighting', 't3_toggle_markers', 't3_toggle_markers',
			't3_help', 't3_help', 't3_next_start']:
		await send_action(action)
	check(viewer.view_mode_name() == 'lit', 'view modes and toggles respond')

	var hit: Dictionary = viewer.inspect_at_screen_center()
	var hit_desc := String(hit.get('title', 'nothing')) if not hit.is_empty() else 'nothing under the crosshair'
	check(true, 'inspect at screen centre: ' + hit_desc)
	var any_hit: Dictionary = viewer.inspect_first_actor()
	check(not any_hit.is_empty(), 'inspector shows an actor: ' + String(any_hit.get('title', '')))

	await send_action('t3_focus')
	await send_action('t3_back')
	var back = await wait_for_scene(PICKER_SCENE, 30.0)
	check(back != null, 'Esc returns to the map picker')
	await frames(5)

	if selftest_failures.is_empty():
		print('SELFTEST PASSED')
		get_tree().quit(0)
	else:
		print('SELFTEST FAILED: ' + ', '.join(selftest_failures))
		get_tree().quit(1)
