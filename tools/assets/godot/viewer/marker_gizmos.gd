extends RefCounted

## Small coloured boxes for actors that have no geometry of their own (player
## starts, AI points, standalone lights, sounds, volumes, emitters...), so they
## can be seen and picked.  The boxes are children of the actor nodes (tagged
## with the 't3_gizmo' meta) and keep a constant size whatever the actor scale.

# =============================================================================
# VARIABLES
# =============================================================================

## Actor nodes that received a gizmo.
var targets: Array[Node3D] = []

## The gizmo mesh instances themselves, parallel to `targets`.
var gizmos: Array[Node3D] = []

## Whether gizmos are currently shown.
var visible := true

# =============================================================================
# CONSTANTS
# =============================================================================

## Gizmo colour per category, as returned by category().
const COLORS := {
	'start': Color(0.35, 1.0, 0.45),
	'light': Color(1.0, 0.86, 0.35),
	'ai': Color(0.35, 0.8, 1.0),
	'volume': Color(0.78, 0.5, 1.0),
	'sound': Color(1.0, 0.55, 0.25),
	'fx': Color(1.0, 0.4, 0.6),
	'other': Color(0.72, 0.74, 0.8),
}

# =============================================================================
# METHODS
# =============================================================================

## The gizmo category for `node`, guessed from its class, base class and
## archetype name (or 'light' for any Light3D).
static func category(node: Node) -> String:
	if node is Light3D:
		return 'light'

	var text := (String(node.get_meta('t3_class', '')) + ' ' + String(node.get_meta('t3_base', '')) + ' '
		+ String(node.get_meta('t3_archetype', ''))).to_lower()
	if text.contains('playerstart'):
		return 'start'
	if text.contains('sound'):
		return 'sound'
	if text.contains('volume') or text.contains('zone'):
		return 'volume'
	if text.contains('emitter') or text.contains('flame') or text.contains('smoke'):
		return 'fx'
	if text.contains('point') or text.contains('ai') or text.contains('patrol'):
		return 'ai'
	return 'other'

## Adds gizmos to every Marker3D and every light that is not part of a mesh actor.
func build(map_root: Node, size: float = 0.16) -> void:
	var box := BoxMesh.new()
	box.size = Vector3.ONE * size
	var nose := BoxMesh.new()
	nose.size = Vector3(size * 1.6, size * 0.3, size * 0.3)
	var mats := {}
	for key in COLORS:
		var m := StandardMaterial3D.new()
		m.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED
		m.albedo_color = COLORS[key]
		mats[key] = m

	for n in map_root.find_children('*', 'Node3D', true, false):
		var is_marker := n is Marker3D

		# Skip lights with no actor of their own (e.g. the preview sun).
		var is_light := n is Light3D and n.has_meta('t3_name')
		if not (is_marker or is_light):
			continue

		var cat := category(n)
		var g := MeshInstance3D.new()
		g.name = '_t3_gizmo'
		g.mesh = box
		g.material_override = mats[cat]
		g.cast_shadow = GeometryInstance3D.SHADOW_CASTING_SETTING_OFF
		g.set_meta('t3_gizmo', true)

		if cat == 'start':
			# A nose along the actor's forward axis (Unreal +X is Godot +X).
			var tip := MeshInstance3D.new()
			tip.mesh = nose
			tip.material_override = mats[cat]
			tip.position = Vector3(size * 0.9, 0, 0)
			tip.cast_shadow = GeometryInstance3D.SHADOW_CASTING_SETTING_OFF
			tip.set_meta('t3_gizmo', true)
			g.add_child(tip)

		n.add_child(g)
		var s := (n as Node3D).global_transform.basis.get_scale()

		# Counteract the actor's own scale.
		if s.x > 1e-4 and s.y > 1e-4 and s.z > 1e-4:
			g.scale = Vector3(1.0 / s.x, 1.0 / s.y, 1.0 / s.z)

		targets.append(n)
		gizmos.append(g)

## Shows or hides every gizmo.
func set_visible(on: bool) -> void:
	visible = on
	for g in gizmos:
		if is_instance_valid(g):
			g.visible = on

## Number of gizmo targets per category.
func count_by_category() -> Dictionary:
	var out := {}
	for t in targets:
		var c := category(t)
		out[c] = int(out.get(c, 0)) + 1
	return out
