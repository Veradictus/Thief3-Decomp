extends MeshInstance3D

## Oriented wire box around the selected object, drawn on top of the scene.

# =============================================================================
# VARIABLES
# =============================================================================

## The line geometry rebuilt each time show_for() is called.
var _lines := ImmediateMesh.new()

## The node the box currently outlines, or null when hidden.
var target: Node3D = null

# =============================================================================
# CONSTANTS
# =============================================================================

## The picking helper, for its local_bounds() utility.
const Pick := preload('res://t3_tools/viewer/t3_pick.gd')

# =============================================================================
# METHODS
# =============================================================================

## Builds the unshaded, always-on-top wire material and starts hidden.
func _init() -> void:
	mesh = _lines
	var m := StandardMaterial3D.new()
	m.shading_mode = BaseMaterial3D.SHADING_MODE_UNSHADED
	m.albedo_color = Color(1.0, 0.62, 0.2)
	m.no_depth_test = true
	m.render_priority = 10
	material_override = m
	cast_shadow = GeometryInstance3D.SHADOW_CASTING_SETTING_OFF
	set_meta('t3_gizmo', true)
	visible = false

## Shows an oriented wire box around `node`'s local bounds, or hides the box
## if `node` is null or has been freed.
func show_for(node: Node3D) -> void:
	target = node
	if node == null or not is_instance_valid(node):
		hide_box()
		return

	var box := Pick.local_bounds(node).grow(0.02)
	global_transform = node.global_transform

	_lines.clear_surfaces()
	_lines.surface_begin(Mesh.PRIMITIVE_LINES)
	var p := box.position
	var s := box.size

	# The box's 8 corners.
	var c := [p, p + Vector3(s.x, 0, 0), p + Vector3(s.x, 0, s.z), p + Vector3(0, 0, s.z),
		p + Vector3(0, s.y, 0), p + Vector3(s.x, s.y, 0), p + s, p + Vector3(0, s.y, s.z)]

	# The 12 edges, as pairs of corner indices.
	for e in [0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7]:
		_lines.surface_add_vertex(c[e])
	_lines.surface_end()

	visible = true

## Hides the box and clears the target.
func hide_box() -> void:
	target = null
	visible = false
