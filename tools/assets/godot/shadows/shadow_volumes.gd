@tool
extends RefCounted

## One exported map's stencil-shadow data, for T3Shadows (t3_shadows.gd).
##
## - Reads the shadow volumes the export wrote (.t3shadow files, named by the
##   t3_shadow metadata of mesh actors and of the BSP node) and uploads them
##   to the effect, as `casters`.
## - Swaps the map's imported StandardMaterial3Ds for t3_lit materials with
##   the same settings (convert_materials()), and puts them back
##   (restore_materials()).
## - Works out which casters a light ignores (ignored_casters()).

# =============================================================================
# VARIABLES
# =============================================================================

## The map's root node (the one with t3_level metadata).
var root: Node3D

## Shadow casters: [{'node': Node3D, 'mesh': int (effect mesh), 'center':
## Vector3 (world), 'radius': float (world)}].
var casters: Array = []

## The effect meshes this map uploaded, for release().
var mesh_ids: Array = []

## The volume meshes as read, for encloses(): {effect mesh index: entry}.
var _cpu := {}

## Casters by actor name (t3_name), for attachments.
var _by_name := {}

## The casters each light ignores: {Light3D: {caster index: true}}.
var _ignored := {}

## Meshes changed: [[MeshInstance3D, previous layers, [[surface, previous override]...]]].
var _overrides: Array = []

## t3_lit materials made so far: {BaseMaterial3D: ShaderMaterial or null}.
var _lit := {}

# =============================================================================
# CONSTANTS
# =============================================================================

## The .t3shadow reader.
const ShadowFile := preload('res://t3_tools/shadows/shadow_file.gd')

## The node-metadata reader.
const Meta := preload('res://t3_tools/viewer/t3_meta.gd')

## The render layer (20) of converted meshes.
const LIT_LAYER := 1 << 19

## The lit shaders: opaque and alpha-tested.
const LIT_SHADER := preload('res://t3_tools/shadows/t3_lit.gdshader')
const LIT_MASKED_SHADER := preload('res://t3_tools/shadows/t3_lit_masked.gdshader')

## BaseMaterial3D features t3_lit does not have: a material using one keeps
## its own look (and gets no volume shadows).
const UNSUPPORTED_FEATURES := [BaseMaterial3D.FEATURE_RIM, BaseMaterial3D.FEATURE_CLEARCOAT,
	BaseMaterial3D.FEATURE_ANISOTROPY, BaseMaterial3D.FEATURE_AMBIENT_OCCLUSION,
	BaseMaterial3D.FEATURE_HEIGHT_MAPPING, BaseMaterial3D.FEATURE_SUBSURFACE_SCATTERING,
	BaseMaterial3D.FEATURE_SUBSURFACE_TRANSMITTANCE, BaseMaterial3D.FEATURE_BACKLIGHT,
	BaseMaterial3D.FEATURE_REFRACTION, BaseMaterial3D.FEATURE_DETAIL, BaseMaterial3D.FEATURE_BENT_NORMAL_MAPPING]

# =============================================================================
# METHODS
# =============================================================================

## Reads and uploads the volumes of the map under `map_root` into `effect`.
func _init(map_root: Node3D, effect) -> void:
	root = map_root

	# One upload per file, shared by every actor using the mesh.
	var uploaded := {}
	var nodes: Array[Node] = [map_root]
	nodes.append_array(map_root.find_children('*', 'Node3D', true, false))
	for n in nodes:
		if not n.has_meta('t3_shadow') or not (n as Node3D).is_visible_in_tree():
			continue

		var path := String(n.get_meta('t3_shadow'))
		if not uploaded.has(path):
			var meshes: Array = []
			for entry in ShadowFile.read(path):
				var id: int = effect.add_volume_mesh(entry)
				if id >= 0:
					_cpu[id] = entry
					mesh_ids.append(id)
				meshes.append([id, entry['center'], entry['radius']])
			uploaded[path] = meshes

		var xf := (n as Node3D).global_transform
		var scale := maxf(xf.basis.get_scale().x, maxf(xf.basis.get_scale().y, xf.basis.get_scale().z))
		for m in uploaded[path]:
			if int(m[0]) >= 0:
				casters.append({'node': n, 'mesh': int(m[0]), 'center': xf * (m[1] as Vector3),
					'radius': float(m[2]) * scale})
		if n.has_meta('t3_name'):
			_by_name[String(n.get_meta('t3_name'))] = n

## Puts the materials back and frees the map's meshes in `effect`.
func release(effect) -> void:
	restore_materials()
	effect.free_meshes(mesh_ids)
	mesh_ids.clear()
	casters.clear()

# --- Materials ---

## Puts t3_lit materials on the map's imported meshes (see lit_material()),
## and moves those meshes to render layer LIT_LAYER only, where the stand-in
## lights of t3_shadows.gd reach them.  Only meshes inside the map's .glb
## instances change, never nodes of the map scene itself: nothing of this is
## saved with the scene, and a user's own meshes keep their materials.
func convert_materials() -> void:
	if not _overrides.is_empty():
		return
	for mi in root.find_children('*', 'MeshInstance3D', true, false):
		var m := mi as MeshInstance3D
		if m.mesh == null or m.material_override != null or m.owner == root or m.owner == null:
			continue
		var surfaces: Array = []
		for s in m.mesh.get_surface_count():
			var lit := lit_material(m.get_active_material(s))
			if lit != null:
				surfaces.append([s, m.get_surface_override_material(s)])
				m.set_surface_override_material(s, lit)
		if not surfaces.is_empty():
			_overrides.append([m, m.layers, surfaces])
			m.layers = LIT_LAYER

## Puts the map's own materials and layers back.
func restore_materials() -> void:
	for o in _overrides:
		var m := o[0] as MeshInstance3D
		if not is_instance_valid(m):
			continue
		m.layers = o[1]
		for s in o[2]:
			m.set_surface_override_material(s[0], s[1])
	_overrides.clear()

## A t3_lit material standing in for `mat`, or null when `mat` is not a
## BaseMaterial3D or uses something t3_lit does not have (unshaded, blended,
## not back-face culled, rim, clearcoat, roughness or metallic textures,
## triplanar mapping...).  Such a material stays as it is: it looks right but
## gets no volume shadows.
func lit_material(mat: Material) -> ShaderMaterial:
	if not (mat is BaseMaterial3D):
		return null
	if _lit.has(mat):
		return _lit[mat]

	var b := mat as BaseMaterial3D
	_lit[mat] = null
	var masked := b.transparency == BaseMaterial3D.TRANSPARENCY_ALPHA_SCISSOR
	if b.shading_mode != BaseMaterial3D.SHADING_MODE_PER_PIXEL or b.cull_mode != BaseMaterial3D.CULL_BACK \
			or not (masked or b.transparency == BaseMaterial3D.TRANSPARENCY_DISABLED) \
			or b.diffuse_mode != BaseMaterial3D.DIFFUSE_BURLEY \
			or b.specular_mode != BaseMaterial3D.SPECULAR_SCHLICK_GGX \
			or b.billboard_mode != BaseMaterial3D.BILLBOARD_DISABLED \
			or b.roughness_texture != null or b.metallic_texture != null \
			or b.uv1_triplanar or b.uv2_triplanar or b.grow or b.proximity_fade_enabled \
			or b.distance_fade_mode != BaseMaterial3D.DISTANCE_FADE_DISABLED or b.next_pass != null:
		return null
	for f in UNSUPPORTED_FEATURES:
		if b.get_feature(f):
			return null

	var sm := ShaderMaterial.new()
	sm.shader = LIT_MASKED_SHADER if masked else LIT_SHADER
	sm.resource_name = b.resource_name
	sm.render_priority = b.render_priority
	sm.set_shader_parameter('albedo', b.albedo_color)
	if b.albedo_texture != null:
		sm.set_shader_parameter('albedo_texture', b.albedo_texture)
	sm.set_shader_parameter('use_vertex_color', b.vertex_color_use_as_albedo)
	sm.set_shader_parameter('vertex_color_srgb', b.vertex_color_is_srgb)
	if b.normal_enabled and b.normal_texture != null:
		sm.set_shader_parameter('normal_texture', b.normal_texture)
		sm.set_shader_parameter('normal_scale', b.normal_scale)
	if b.emission_enabled:
		sm.set_shader_parameter('emission', b.emission)
		sm.set_shader_parameter('emission_energy', b.emission_energy_multiplier)
		if b.emission_texture != null:
			sm.set_shader_parameter('emission_texture', b.emission_texture)
	sm.set_shader_parameter('roughness', b.roughness)
	sm.set_shader_parameter('metallic', b.metallic)
	sm.set_shader_parameter('specular', b.metallic_specular)
	sm.set_shader_parameter('uv1_scale', b.uv1_scale)
	sm.set_shader_parameter('uv1_offset', b.uv1_offset)
	sm.set_shader_parameter('alpha_scissor_threshold', b.alpha_scissor_threshold)
	# The inspector reads the T3 material data from the glTF extras.
	for k in b.get_meta_list():
		sm.set_meta(k, b.get_meta(k))
	_lit[mat] = sm
	return sm

# --- Casters ---

## The casters light `l` ignores, as {caster index: true}: its own actor, the
## actor it is attached to, and casters that enclose it (encloses()).
## Worked out once per light.
func ignored_casters(l: Light3D) -> Dictionary:
	if _ignored.has(l):
		return _ignored[l]

	var own := {}
	var actor := Meta.actor_node(l)
	if actor != null:
		own[actor] = true
		if actor.has_meta('t3_attached_to'):
			var parent = _by_name.get(String(actor.get_meta('t3_attached_to')), null)
			if parent != null:
				own[parent] = true

	var out := {}
	var p := l.global_position
	for ci in casters.size():
		var c: Dictionary = casters[ci]
		if own.has(c['node']) or (p.distance_to(c['center']) <= float(c['radius']) and encloses(c, p)):
			out[ci] = true
	_ignored[l] = out
	return out

## Whether caster `c`'s volume mesh holds point `p` (world) inside faces
## turned outward: a ray from `p` leaves through more faces than it enters.
## The volume of a light inside such a shell is the shell's inside, so the
## light would light nothing in it (an exterior mesh around a room, which T3
## keeps apart from the room's lights, probably by zone).  A room's own
## inward-facing walls do not count: their faces turn towards the light.
func encloses(c: Dictionary, p: Vector3) -> bool:
	var m: Dictionary = _cpu[c['mesh']]
	var lp := (c['node'] as Node3D).global_transform.affine_inverse() * p
	var pos: PackedByteArray = m['positions']
	var nrm: PackedByteArray = m['normals']
	var idx: PackedByteArray = m['indices']
	var wide := int(m['index_size']) == 4
	# Skewed, so the ray does not run along the edges of axis-aligned meshes.
	var dir := Vector3(0.5773, 0.5779, 0.5767).normalized()
	var crossings := 0
	for t in int(m['index_count']) / 3:
		var v: Array[int] = []
		for k in 3:
			v.append(int(idx.decode_u32((t * 3 + k) * 4)) if wide else idx.decode_u16((t * 3 + k) * 2))
		var a := Vector3(pos.decode_float(v[0] * 12), pos.decode_float(v[0] * 12 + 4), pos.decode_float(v[0] * 12 + 8))
		var b := Vector3(pos.decode_float(v[1] * 12), pos.decode_float(v[1] * 12 + 4), pos.decode_float(v[1] * 12 + 8))
		var e := Vector3(pos.decode_float(v[2] * 12), pos.decode_float(v[2] * 12 + 4), pos.decode_float(v[2] * 12 + 8))
		# The edges' degenerate triangles have no area and are never hit.
		if Geometry3D.ray_intersects_triangle(lp, dir, a, b, e) != null:
			var n := Vector3(nrm.decode_s8(v[0] * 4), nrm.decode_s8(v[0] * 4 + 1), nrm.decode_s8(v[0] * 4 + 2))
			crossings += 1 if n.dot(dir) > 0.0 else -1
	return crossings > 0
