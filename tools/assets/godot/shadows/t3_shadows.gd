@tool
extends Node

## Autoload "T3Shadows": T3's stencil shadows for exported maps, with no
## setup.  It runs in the game, in the viewer and in the editor's 3D view.
##
## What a user sees:
## - Project Settings > T3 > Shadows: Enabled, Max Shadowed Lights (0-4).
##   At run time, set T3Shadows.enabled or T3Shadows.max_shadowed_lights.
## - A light casts shadows when its own Shadow > Enabled is on (the export
##   turns it on for the lights that cast shadows in T3).  The nearest such
##   lights get volume shadows; the others keep Godot's shadow maps.
## Nothing else changes in a scene: no light, node or material property is
## touched, so nothing of this is saved.
##
## What it does:
## - Finds exported maps as they enter the tree (the root carries t3_level)
##   and loads their shadow volumes (shadow_volumes.gd).
## - Swaps the maps' imported StandardMaterial3Ds for t3_lit materials, which
##   look the same and read the shadow mask, and moves those meshes to render
##   layer 20.  A user's own meshes and materials stay as they are.
## - Puts the effect (stencil_shadow_effect.gd) on the current camera.
## - Every frame, gives the nearest shadowed omni and spot lights in view a
##   mask channel.  Such a light is hidden on the RenderingServer and drawn
##   by two stand-in lights made there, copies of it: one lights layer 20
##   only, without a shadow map, and passes the channel in its specular
##   amount (t3_lit.gdshaderinc); the other lights every other layer as the
##   light itself would, shadow map included.
## - Without the Forward+ renderer on a GPU (Compatibility, headless) it
##   prints one warning and does nothing: lights keep Godot's shadow maps.

# =============================================================================
# VARIABLES
# =============================================================================

## Whether volume shadows are on.  Off: maps and lights are as exported.
var enabled := true:
	set(v):
		enabled = v
		_dirty = true

## How many lights get volume shadows at once (0-4).
var max_shadowed_lights := 4:
	set(v):
		max_shadowed_lights = clampi(v, 0, Effect.MAX_LIGHTS)

## Whether the renderer can draw them (Forward+ on a GPU).
var supported := false

## The effect, and the Compositor holding it while no camera has its own.
var _effect: Effect
var _compositor := Compositor.new()

## The camera the effect is on, and the Compositor there.
var _camera: Camera3D
var _camera_compositor: Compositor

## Registered maps: {map root: ShadowVolumes}.
var _maps := {}

## Omni and spot lights in the tree (in the editor: in the edited scene).
var _lights: Array[Light3D] = []

## Lights holding a mask channel: {Light3D: slot}.
var _slots := {}

## The stand-in lights of the lights holding a channel: {Light3D: [volume
## light RID, volume instance RID, other light RID, other instance RID]}.
var _standins := {}

## Settings changed: maps and lights are brought in line next frame.
var _dirty := true

## The edited scene (editor only).
var _edited: Node

# =============================================================================
# CONSTANTS
# =============================================================================

## The effect script.
const Effect := preload('res://t3_tools/shadows/stencil_shadow_effect.gd')

## One map's shadow data.
const ShadowVolumes := preload('res://t3_tools/shadows/shadow_volumes.gd')

## The project settings.
const SETTING_ENABLED := 't3/shadows/enabled'
const SETTING_MAX_LIGHTS := 't3/shadows/max_shadowed_lights'

## What a channel adds to a stand-in's specular: (slot + 1) * this.  A real
## light's specular stays below half of it (t3_lit.gdshaderinc).
const SLOT_SPECULAR := 32.0

# =============================================================================
# METHODS
# =============================================================================

## Reads the settings, makes the effect, and starts watching the tree.
func _ready() -> void:
	_define_setting(SETTING_ENABLED, true, TYPE_BOOL, PROPERTY_HINT_NONE, '')
	_define_setting(SETTING_MAX_LIGHTS, 4, TYPE_INT, PROPERTY_HINT_RANGE, '0,4')
	enabled = bool(ProjectSettings.get_setting(SETTING_ENABLED, true))
	max_shadowed_lights = int(ProjectSettings.get_setting(SETTING_MAX_LIGHTS, 4))

	_effect = Effect.new()
	supported = _effect.is_supported()
	if not supported:
		var why := 'T3 shadows are off: they need the Forward+ renderer on a GPU. Lights use Godot\'s shadow maps.'
		if DisplayServer.get_name() == 'headless':
			print(why)
		else:
			push_warning(why)
		set_process(false)
		return

	_compositor.compositor_effects = [_effect]
	get_tree().node_added.connect(_on_node_added)
	if not Engine.is_editor_hint():
		_on_node_added(get_tree().root)
		for n in get_tree().root.find_children('*', '', true, false):
			_on_node_added(n)

## Declares a project setting with its default and hint, so it shows in
## Project Settings without the advanced view.
func _define_setting(name: String, default: Variant, type: int, hint: int, hint_string: String) -> void:
	if not ProjectSettings.has_setting(name):
		ProjectSettings.set_setting(name, default)
	ProjectSettings.set_initial_value(name, default)
	ProjectSettings.add_property_info({'name': name, 'type': type, 'hint': hint, 'hint_string': hint_string})
	ProjectSettings.set_as_basic(name, true)

## A short status line, for a HUD.
func status_text() -> String:
	if not supported:
		return 'Shadows: shadow maps only (volume shadows need Forward+ on a GPU)'
	if not enabled:
		return 'Shadows: shadow maps only (volume shadows off)'
	var casters := 0
	for m in _maps.values():
		casters += m.casters.size()
	var shadowed := 0
	for l in _lights:
		if is_instance_valid(l) and l.shadow_enabled:
			shadowed += 1
	return 'Shadows: volumes for %d of %d lights, %d casters, %d draws' % [_slots.size(), shadowed, casters,
		_effect.draws]

# --- Tree ---

## Tracks lights, and registers maps once their children are in.
func _on_node_added(n: Node) -> void:
	if Engine.is_editor_hint() and not _in_edited_scene(n):
		return
	if n is OmniLight3D or n is SpotLight3D:
		if not _lights.has(n):
			_lights.append(n)
	if n is Node3D and n.has_meta('t3_level') and not _maps.has(n):
		_register.call_deferred(n)

## Whether `n` belongs to the scene open in the editor.
func _in_edited_scene(n: Node) -> bool:
	var root := _edited_scene_root()
	return root != null and (n == root or root.is_ancestor_of(n))

## The scene open in the editor, or null (also outside the editor).  The
## EditorInterface singleton is looked up by name: exported games lack it.
func _edited_scene_root() -> Node:
	if not Engine.is_editor_hint():
		return null
	return Engine.get_singleton('EditorInterface').get_edited_scene_root()

## Loads a map's volumes; it is dropped again when it leaves the tree.
func _register(root: Node3D) -> void:
	if not is_instance_valid(root) or not root.is_inside_tree() or _maps.has(root):
		return
	_maps[root] = ShadowVolumes.new(root, _effect)
	root.tree_exiting.connect(_unregister.bind(root))
	_dirty = true

## Puts a map back as it was and frees its volumes.
func _unregister(root: Node3D) -> void:
	var m = _maps.get(root)
	if m == null:
		return
	_maps.erase(root)
	if is_instance_valid(root) and root.tree_exiting.is_connected(_unregister.bind(root)):
		root.tree_exiting.disconnect(_unregister.bind(root))
	_release_lights()
	_effect.lights = []
	_effect.casters = []
	m.release(_effect)

# --- Frames ---

## Follows the edited scene (editor), the camera and the settings, then picks
## this frame's shadowed lights.
func _process(_delta: float) -> void:
	if Engine.is_editor_hint():
		_follow_edited_scene()

	var on := enabled and max_shadowed_lights > 0 and not _maps.is_empty()
	# Stand-ins go before the meshes leave their layer: the RenderingServer
	# unpairs a light from the meshes its cull mask matches at that moment.
	if not on:
		_release_lights()
	if _dirty:
		_dirty = false
		for m in _maps.values():
			if on:
				m.convert_materials()
			else:
				m.restore_materials()
	_attach(_current_camera() if on else null)
	if not on or _camera == null:
		return
	_effect.update_targets()
	_update_lights()

## In the editor, registers the scene being edited when it is a map, and
## drops the one that was.
func _follow_edited_scene() -> void:
	var root := _edited_scene_root()
	if root == _edited:
		return
	for m in _maps.keys():
		_unregister(m)
	_release_lights()
	_lights.clear()
	_edited = root
	if root != null:
		_on_node_added(root)
		for n in root.find_children('*', '', true, false):
			_on_node_added(n)

## The camera to draw for: the game's current camera, or the editor's first
## 3D view.
func _current_camera() -> Camera3D:
	if Engine.is_editor_hint():
		var vp: SubViewport = Engine.get_singleton('EditorInterface').get_editor_viewport_3d(0)
		return vp.get_camera_3d() if vp != null else null
	return get_viewport().get_camera_3d()

## Puts the effect on `cam` (null: on no camera).  A camera with a Compositor
## of its own gets the effect added to it, and removed again later.
func _attach(cam: Camera3D) -> void:
	if cam == _camera and (cam == null or cam.compositor == _camera_compositor):
		return
	if is_instance_valid(_camera) and _camera_compositor != null:
		if _camera_compositor == _compositor:
			if _camera.compositor == _compositor:
				_camera.compositor = null
		else:
			var effects := _camera_compositor.compositor_effects
			effects.erase(_effect)
			_camera_compositor.compositor_effects = effects
	_camera = cam
	_camera_compositor = null
	if cam == null:
		return
	if cam.compositor == null:
		cam.compositor = _compositor
	elif cam.compositor != _compositor and not cam.compositor.compositor_effects.has(_effect):
		var effects := cam.compositor.compositor_effects
		effects.append(_effect)
		cam.compositor.compositor_effects = effects
	_camera_compositor = cam.compositor

## Picks the shadowed lights, updates their stand-ins, and hands lights and
## casters to the effect.
func _update_lights() -> void:
	var kept: Array[Light3D] = []
	for l in _lights:
		if is_instance_valid(l) and l.is_inside_tree():
			kept.append(l)
		elif _slots.has(l):
			_drop_standins(l)
	_lights = kept

	# The nearest shadowed lights whose range is in view.
	var eye := _camera.global_position
	var planes := _camera.get_frustum()
	var ranked: Array = []
	for l in _lights:
		if not l.shadow_enabled or not l.is_visible_in_tree():
			continue
		var r := light_range(l)
		var p := l.global_position
		if r > 0.0 and sphere_in_frustum(p, r, planes):
			ranked.append([maxf(p.distance_to(eye) - r, 0.0) + p.distance_to(eye) * 0.01, l])
	ranked.sort_custom(func(a, b): return a[0] < b[0])
	var chosen: Array = []
	for i in mini(max_shadowed_lights, ranked.size()):
		chosen.append(ranked[i][1])

	# Keep the channels of lights that stay, so the mask does not shuffle.
	var slots := {}
	var used := {}
	for l in chosen:
		if _slots.has(l):
			slots[l] = _slots[l]
			used[_slots[l]] = true
	for l in chosen:
		if not slots.has(l):
			var s := 0
			while used.has(s):
				s += 1
			slots[l] = s
			used[s] = true
	for l in _slots:
		if not slots.has(l):
			_drop_standins(l)
	_slots = slots
	for l in slots:
		_update_standins(l, slots[l])

	# Each light's casters: bounding spheres that meet its range.
	var frame_casters: Array = []
	var frame_lights: Array = []
	for l in slots:
		var p := (l as Light3D).global_position
		var r := light_range(l)
		var mine: Array = []
		for m in _maps.values():
			var skip: Dictionary = m.ignored_casters(l)
			for ci in m.casters.size():
				var c: Dictionary = m.casters[ci]
				if skip.has(ci) or p.distance_to(c['center']) > r + float(c['radius']):
					continue
				mine.append(frame_casters.size())
				frame_casters.append({'mesh': c['mesh'], 'xform': (c['node'] as Node3D).global_transform})
		frame_lights.append({'pos': p, 'slot': slots[l], 'casters': mine})
	_effect.casters = frame_casters
	_effect.lights = frame_lights

# --- Stand-in lights ---

## Makes or updates the two stand-ins of light `l` (channel `slot`) and hides
## `l` itself, on the RenderingServer only.  They copy every light parameter
## each frame, so editing the light shows at once.
func _update_standins(l: Light3D, slot: int) -> void:
	if not _standins.has(l):
		var ids: Array = []
		for k in 2:
			var base := RenderingServer.omni_light_create() if l is OmniLight3D else RenderingServer.spot_light_create()
			ids.append(base)
			ids.append(RenderingServer.instance_create2(base, l.get_world_3d().scenario))
		_standins[l] = ids
	var ids: Array = _standins[l]
	RenderingServer.instance_set_visible(l.get_instance(), false)
	for k in 2:
		var base: RID = ids[k * 2]
		var inst: RID = ids[k * 2 + 1]
		RenderingServer.instance_set_transform(inst, l.global_transform)
		RenderingServer.instance_set_layer_mask(inst, l.layers)
		for p in Light3D.PARAM_MAX:
			RenderingServer.light_set_param(base, p as RenderingServer.LightParam, l.get_param(p as Light3D.Param))
		RenderingServer.light_set_color(base, _light_color(l))
		RenderingServer.light_set_negative(base, l.light_negative)
		RenderingServer.light_set_distance_fade(base, l.distance_fade_enabled, l.distance_fade_begin, l.distance_fade_shadow,
			l.distance_fade_length)
		RenderingServer.light_set_projector(base, l.light_projector.get_rid() if l.light_projector != null else RID())
		RenderingServer.light_set_reverse_cull_face_mode(base, l.shadow_reverse_cull_face)
		RenderingServer.light_set_shadow_caster_mask(base, l.shadow_caster_mask)
		if l is OmniLight3D:
			var mode := int((l as OmniLight3D).omni_shadow_mode) as RenderingServer.LightOmniShadowMode
			RenderingServer.light_omni_set_shadow_mode(base, mode)
	# Volume stand-in: t3_lit surfaces only, no shadow map, the channel in the specular.
	RenderingServer.light_set_cull_mask(ids[0], l.light_cull_mask & ShadowVolumes.LIT_LAYER)
	RenderingServer.light_set_shadow(ids[0], false)
	RenderingServer.light_set_param(ids[0], RenderingServer.LIGHT_PARAM_SPECULAR,
		clampf(l.light_specular, 0.0, SLOT_SPECULAR * 0.5 - 0.01) + SLOT_SPECULAR * (slot + 1))
	# The other stand-in: everything else, as the light itself.
	RenderingServer.light_set_cull_mask(ids[2], l.light_cull_mask & ~ShadowVolumes.LIT_LAYER)
	RenderingServer.light_set_shadow(ids[2], l.shadow_enabled)

## Frees the stand-ins of `l` and shows `l` itself again.
func _drop_standins(l: Light3D) -> void:
	var ids: Array = _standins.get(l, [])
	for k in [1, 3, 0, 2]:
		if k < ids.size():
			RenderingServer.free_rid(ids[k])
	_standins.erase(l)
	if is_instance_valid(l) and l.is_inside_tree():
		RenderingServer.instance_set_visible(l.get_instance(), l.is_visible_in_tree())

## Drops every stand-in.
func _release_lights() -> void:
	for l in _standins.keys():
		_drop_standins(l)
	_slots.clear()

## The colour Light3D itself passes to the RenderingServer.
static func _light_color(l: Light3D) -> Color:
	if not ProjectSettings.get_setting('rendering/lights_and_shadows/use_physical_light_units', false):
		return l.light_color
	return (l.light_color.srgb_to_linear() * l.get_correlated_color().srgb_to_linear()).linear_to_srgb()

## The range of light `l`, in metres.
static func light_range(l: Light3D) -> float:
	if l is OmniLight3D:
		return (l as OmniLight3D).omni_range
	if l is SpotLight3D:
		return (l as SpotLight3D).spot_range
	return 0.0

## Whether the sphere (`c`, `r`) meets the frustum `planes`
## (Camera3D.get_frustum(), normals pointing out).
static func sphere_in_frustum(c: Vector3, r: float, planes: Array[Plane]) -> bool:
	for p in planes:
		if p.distance_to(c) > r:
			return false
	return true

## Puts maps and lights back and frees the GPU resources when the autoload
## goes (the game quits, the plugin reloads).
func _exit_tree() -> void:
	if _effect == null:
		return
	for m in _maps.keys():
		_unregister(m)
	_release_lights()
	_attach(null)
	_compositor.compositor_effects = []
	_effect.release()
