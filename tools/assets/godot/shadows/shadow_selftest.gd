extends SceneTree

## Checks .t3shadow files with the viewer's own reader (shadow_file.gd), and
## uploads them when a RenderingDevice exists.  Prints one line per file:
##   OK <path> meshes <n> with_data <m> vertices <v> triangles <t> first <x y z> <nx ny nz> sphere <cx cy cz r>
## and exits with 1 if any file fails.  godot_check.py --shadow-selftest
## compares the line with what Python reads from the same file.
##
## Usage:
##   godot --headless --path <project> --script res://t3_tools/shadows/shadow_selftest.gd -- <file.t3shadow>...

# =============================================================================
# CONSTANTS
# =============================================================================

## The .t3shadow reader.
const ShadowFile := preload('res://t3_tools/shadows/shadow_file.gd')

## The effect, for the upload check.
const Effect := preload('res://t3_tools/shadows/stencil_shadow_effect.gd')

# =============================================================================
# METHODS
# =============================================================================

## Checks every file named on the command line, then quits.
func _init() -> void:
	var failed := false
	var effect := Effect.new()
	for path in OS.get_cmdline_user_args():
		var problem := check_file(path, effect)
		if problem != '':
			print('FAIL %s: %s' % [path, problem])
			failed = true
	if effect.is_supported():
		print('uploaded %d volume meshes' % effect.mesh_count())
	effect.release()
	quit(1 if failed else 0)

## Checks one file; returns what is wrong, or '' (and prints its OK line).
func check_file(path: String, effect: Effect) -> String:
	var meshes := ShadowFile.read(path)
	if meshes.is_empty():
		return 'no meshes read'

	var with_data := 0
	var verts := 0
	var tris := 0
	var first := ''
	for m in meshes:
		var nv := int(m['vertex_count'])
		var ni := int(m['index_count'])
		if nv == 0:
			continue
		with_data += 1
		verts += nv
		tris += ni / 3
		var pos: PackedByteArray = m['positions']
		var nrm: PackedByteArray = m['normals']
		var idx: PackedByteArray = m['indices']
		if pos.size() != nv * 12 or nrm.size() != nv * 4 or idx.size() != ni * int(m['index_size']):
			return 'mesh sizes do not match the counts'
		# T3's layout: 3 vertices per face, 4 triangles per face (the face and 2 per edge).
		if nv % 3 != 0 or ni != nv * 4:
			return 'not 3 vertices and 4 triangles per face (%d vertices, %d indices)' % [nv, ni]

		var c: Vector3 = m['center']
		var r: float = m['radius']
		for i in nv:
			var p := Vector3(pos.decode_float(i * 12), pos.decode_float(i * 12 + 4), pos.decode_float(i * 12 + 8))
			if c.distance_to(p) > r * 1.0001 + 1e-4:
				return 'vertex %d is outside the bounding sphere' % i
		for i in ni:
			var v := idx.decode_u16(i * 2) if int(m['index_size']) == 2 else int(idx.decode_u32(i * 4))
			if v >= nv:
				return 'index %d out of range' % i

		if first == '':
			first = '%.6f %.6f %.6f %d %d %d sphere %.6f %.6f %.6f %.6f' % [pos.decode_float(0), pos.decode_float(4),
				pos.decode_float(8), nrm.decode_s8(0), nrm.decode_s8(1), nrm.decode_s8(2), c.x, c.y, c.z, r]
		if effect.is_supported() and effect.add_volume_mesh(m) < 0:
			return 'upload failed'

	print('OK %s meshes %d with_data %d vertices %d triangles %d first %s' % [path, meshes.size(), with_data,
		verts, tris, first])
	return ''
