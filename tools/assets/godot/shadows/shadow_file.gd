@tool
extends RefCounted

## Reads the .t3shadow files written by tools/assets/t3shadow.py (the format
## is described there and in docs/assets.md): shadow-volume meshes in Godot's
## axes and scale, laid out so their bytes go to the GPU as they are.

# =============================================================================
# CONSTANTS
# =============================================================================

## The file magic.
const MAGIC := 'T3SV'

## The format version this reader knows.
const VERSION := 1

## Header and per-mesh entry sizes, in bytes.
const HEADER_SIZE := 16
const ENTRY_SIZE := 32

# =============================================================================
# METHODS
# =============================================================================

## The meshes of the file at `path`, one Dictionary per entry:
## {vertex_count, index_count, index_size (2 or 4), positions, normals, indices
## (PackedByteArray: f32 xyz, snorm8 xyzw, u16 or u32), center (Vector3),
## radius (float)}.  An entry without data has zero counts.  Returns [] and
## reports an error if the file is missing or malformed.
static func read(path: String) -> Array:
	var data := FileAccess.get_file_as_bytes(path)
	if data.size() < HEADER_SIZE:
		push_error('T3 shadows: cannot read %s' % path)
		return []
	return parse(data, path)

## The meshes of a .t3shadow file held in `data` (see read()); `what` names it
## in error messages.
static func parse(data: PackedByteArray, what: String = '') -> Array:
	if data.size() < HEADER_SIZE or data.slice(0, 4).get_string_from_ascii() != MAGIC:
		push_error('T3 shadows: %s is not a .t3shadow file' % what)
		return []
	if data.decode_u32(4) != VERSION:
		push_error('T3 shadows: %s has version %d, expected %d' % [what, data.decode_u32(4), VERSION])
		return []

	var count := data.decode_u32(8)
	if HEADER_SIZE + count * ENTRY_SIZE > data.size():
		push_error('T3 shadows: %s is truncated' % what)
		return []

	var out: Array = []
	for i in count:
		var e := HEADER_SIZE + i * ENTRY_SIZE
		var nv := data.decode_u32(e)
		var ni := data.decode_u32(e + 4)
		var isize := data.decode_u32(e + 8)
		var off := data.decode_u32(e + 12)
		var entry := {
			'vertex_count': nv, 'index_count': ni, 'index_size': isize,
			'center': Vector3(data.decode_float(e + 16), data.decode_float(e + 20), data.decode_float(e + 24)),
			'radius': data.decode_float(e + 28),
			'positions': PackedByteArray(), 'normals': PackedByteArray(), 'indices': PackedByteArray(),
		}
		if nv > 0:
			var pos_end := off + nv * 12
			var nrm_end := pos_end + nv * 4
			var idx_end := nrm_end + ni * isize
			if (isize != 2 and isize != 4) or idx_end > data.size():
				push_error('T3 shadows: %s: mesh %d is malformed' % [what, i])
				return []
			entry['positions'] = data.slice(off, pos_end)
			entry['normals'] = data.slice(pos_end, nrm_end)
			entry['indices'] = data.slice(nrm_end, idx_end)
		out.append(entry)
	return out
