@tool
extends RefCounted

## The map editor's model: finds what changed in an exported Thief: Deadly
## Shadows level, converts it back to Unreal units, and reads and writes the
## edits file (<Level>/<Level>.edits.json, format "t3-map-edits", see
## docs/assets.md section 8).
##
## tools/assets/t3map.py stores on every actor node its placement in the map
## file (t3_origin: location and rotation in Unreal units, draw_scale), its own
## gamesys properties (t3_gamesys, JSON) and their types (t3_gamesys_types).
## Gamesys values edited in the dock live in t3_gamesys_edits (a Dictionary)
## until they are saved; t3_gamesys stays the map's value.  An actor's changes
## are its differences from these originals, so an untouched actor never
## produces anything.  An export applies the level's saved edits (moved nodes,
## t3_gamesys_edits, copies, removed actors), so a scene exported again yields
## the same edits file.
##
## Coordinates (docs/assets.md section 5): Unreal (x, y, z) is Godot (x, z, y)
## times metres per unit, and an actor's basis is UE2's FRotationMatrix
## conjugated by that swap and scaled by DrawScale.  godot_basis() mirrors
## godot_basis() in tools/assets/t3common.py; rotator_from_basis() inverts it.

# =============================================================================
# CONSTANTS
# =============================================================================

## The edits file's format name.
const FORMAT := 't3-map-edits'

## The edits file's format version (tools/assets/formats.json, map_edits).
const VERSION := 2

## The export format this plugin is made for (tools/assets/formats.json,
## map_export); a scene exported by older tools should be exported again.
const EXPORT_VERSION := 1

## Radians per Unreal rotator unit (65536 units per turn).
const ROT_UNIT := TAU / 65536.0

## Default scale for scenes without t3_units_per_meter: 16 units per foot.
const DEFAULT_UNITS_PER_METER := 16.0 / 0.3048

## Node metadata holding the dock's gamesys edits: {property name: value}.
const EDITS_META := 't3_gamesys_edits'

## Below this length of the rotated X axis' horizontal part the actor points
## straight up or down (pitch +-90 degrees), where yaw and roll share one angle.
const GIMBAL_EPS := 1e-6

## A location component counts as moved beyond this many metres, plus
## LOCATION_REL_EPS times its size (Godot keeps positions as 32-bit floats).
const LOCATION_EPS := 1e-5

## See LOCATION_EPS.
const LOCATION_REL_EPS := 5e-7

## A rotation counts as changed when an element of its matrix moves by more
## than this (one rotator unit moves them by up to 1e-4).
const BASIS_EPS := 1e-5

## A scale counts as changed, or as non-uniform, beyond this relative difference.
const SCALE_REL_EPS := 1e-5

## Moved location components are rounded to 1 / LOCATION_ROUND units.
const LOCATION_ROUND := 100.0

## Changed draw scales are rounded to 1 / SCALE_ROUND.
const SCALE_ROUND := 100000.0

## Gamesys properties that are edited through the node instead: DrawScale is
## the node's scale (the edits file's draw_scale).
const NODE_PROPERTIES := ['DrawScale']

## The actor group nodes of scenes exported before t3map.py sorted actors
## into folders (nodes marked t3_folder).
const GROUPS := ['StaticMeshes', 'Lights', 'Markers', 'CharacterParts']

## At most this many names are listed in one warning.
const MAX_LISTED := 8

## The viewer's node-metadata reader (res://t3_tools/ is installed next to the addon).
const Meta := preload('res://t3_tools/viewer/t3_meta.gd')

# =============================================================================
# METHODS
# =============================================================================

# --- Coordinates ---

## Godot basis of an Unreal rotator (pitch, yaw, roll) and a uniform DrawScale.
static func godot_basis(rot: Vector3i, draw_scale: float = 1.0) -> Basis:
	var sp := sin(rot.x * ROT_UNIT)
	var cp := cos(rot.x * ROT_UNIT)
	var sy := sin(rot.y * ROT_UNIT)
	var cy := cos(rot.y * ROT_UNIT)
	var sr := sin(rot.z * ROT_UNIT)
	var cr := cos(rot.z * ROT_UNIT)
	var s := draw_scale

	# Godot's columns are FRotationMatrix's rows (the rotated Unreal X, Z and Y
	# axes, in that order) with Y and Z swapped; computed in double precision.
	return Basis(
		Vector3(cp * cy * s, sp * s, cp * sy * s),
		Vector3(-(cr * sp * cy + sr * sy) * s, cr * cp * s, (cy * sr - cr * sp * sy) * s),
		Vector3((sr * sp * cy - cr * sy) * s, -sr * cp * s, (sr * sp * sy + cr * cy) * s))

## The rotator whose godot_basis() is `b`, which must be a pure rotation.  Of
## the rotators giving the same matrix ((p, y, r), (32768 - p, y + 32768,
## r + 32768), and whole turns of each), returns the one nearest to `ref` (a
## Vector3i), so an unchanged rotation comes back exactly and a changed one
## stays in the original's range.  Without `ref`, returns UE2's own form
## (FMatrix::Rotator(): pitch within +-16384, yaw and roll within a half
## turn).  At pitch +-90 degrees only yaw - roll (or yaw + roll) is defined;
## the yaw of `ref` (or 0) is kept there.
static func rotator_from_basis(b: Basis, ref: Variant = null) -> Vector3i:
	# FRotationMatrix's rows (see godot_basis()), in double precision.
	var xx := float(b.x.x)
	var xy := float(b.x.z)
	var xz := float(b.x.y)
	var y_axis := [float(b.z.x), float(b.z.z), float(b.z.y)]
	var z_axis := [float(b.y.x), float(b.y.z), float(b.y.y)]

	var near: Vector3i = ref if ref is Vector3i else Vector3i.ZERO
	var horizontal := sqrt(xx * xx + xy * xy)
	var pitch := atan2(xz, horizontal) / ROT_UNIT
	var yaw := float(near.y) if horizontal < GIMBAL_EPS else atan2(xy, xx) / ROT_UNIT

	var best := Vector3i.ZERO
	var best_distance := -1
	for flipped in ([false, true] if ref is Vector3i else [false]):
		var p := nearest_turn(32768.0 - pitch if flipped else pitch, near.x)
		var y := nearest_turn(yaw + 32768.0 if flipped else yaw, near.y)

		# Roll against the Y axis of (pitch, yaw, 0), as UE2's FMatrix::Rotator()
		# does; using the rounded yaw keeps the matrix exact at pitch +-90.
		var sy := -sin(y * ROT_UNIT)
		var cy := cos(y * ROT_UNIT)
		var roll := atan2(z_axis[0] * sy + z_axis[1] * cy, y_axis[0] * sy + y_axis[1] * cy) / ROT_UNIT
		var r := nearest_turn(roll, near.z)

		var distance := absi(p - near.x) + absi(y - near.y) + absi(r - near.z)
		if best_distance < 0 or distance < best_distance:
			best_distance = distance
			best = Vector3i(p, y, r)

	if not (ref is Vector3i):
		best = Vector3i(normalize_axis(best.x), normalize_axis(best.y), normalize_axis(best.z))
	return best

## A rotator component in UE2's normalised range, -32768 to 32767 (FRotator::Normalize()).
static func normalize_axis(units: int) -> int:
	return posmod(units + 32768, 65536) - 32768

## `units` (rotator units) moved by whole turns to lie nearest to `ref`, rounded.
static func nearest_turn(units: float, ref: int) -> int:
	return roundi(units + 65536.0 * roundf((ref - units) / 65536.0))

## Godot position of an Unreal location (x, y, z).
static func to_godot(loc: PackedFloat64Array, units_per_meter: float) -> Vector3:
	var m := 1.0 / units_per_meter
	return Vector3(loc[0] * m, loc[2] * m, loc[1] * m)

## Godot transform of an Unreal placement ({location, rotation, draw_scale},
## as returned by origin()).
static func placement_transform(p: Dictionary, units_per_meter: float) -> Transform3D:
	return Transform3D(godot_basis(p['rotation'], p['draw_scale']), to_godot(p['location'], units_per_meter))

## The largest difference between corresponding elements of `a` and `b`.
static func max_difference(a: Basis, b: Basis) -> float:
	var d := 0.0
	for axis in [a.x - b.x, a.y - b.y, a.z - b.z]:
		var v: Vector3 = axis.abs()
		d = maxf(d, maxf(v.x, maxf(v.y, v.z)))
	return d

## `node`'s transform relative to `root` (the level), composed through its
## parents by hand so it also works on a scene that is not in the tree.
static func level_transform(node: Node3D, root: Node) -> Transform3D:
	var t := node.transform
	var p := node.get_parent()

	while p != null and p != root:
		if p is Node3D:
			t = (p as Node3D).transform * t
		p = p.get_parent()

	return t

## The local transform that puts `node` at `level_xform` relative to `root`.
static func local_for_level(node: Node3D, root: Node, level_xform: Transform3D) -> Transform3D:
	var p := node.get_parent()

	# Directly under the level root, or under a plain Node: nothing to undo.
	if p == null or p == root or not (p is Node3D):
		return level_xform

	return level_transform(p as Node3D, root).affine_inverse() * level_xform

# --- Scene Metadata ---

## Unreal units per metre of the level under `root`.
static func units_per_meter(root: Node) -> float:
	return float(root.get_meta('t3_units_per_meter', DEFAULT_UNITS_PER_METER))

## The level's name (the map file's name without extension).
static func level_name(root: Node) -> String:
	return String(root.get_meta('t3_level', root.name))

## Whether `root` is an exported T3 level scene.
static func is_level(root: Node) -> bool:
	return root != null and root.has_meta('t3_level')

## The export format version of the level under `root` (0: exported before
## scenes were stamped with one).
static func export_version(root: Node) -> int:
	return int(root.get_meta('t3_export_version', 0))

## Whether the level under `root` was exported by older tools than this
## plugin is made for (see EXPORT_VERSION).
static func is_outdated(root: Node) -> bool:
	return export_version(root) < EXPORT_VERSION

## The source map ({file, size, sha1}) recorded at export, or {}.
static func source(root: Node) -> Dictionary:
	var s = Meta.json(root, 't3_source')
	if not (s is Dictionary) or not s.has('sha1'):
		return {}

	return {'file': String(s.get('file', '')), 'size': int(s.get('size', 0)), 'sha1': String(s['sha1'])}

## Enum value names of the level's enum properties: {enum type: [names]}.
static func enums(root: Node) -> Dictionary:
	var e = Meta.json(root, 't3_enums')
	return e if e is Dictionary else {}

## An actor node's placement as exported: {location: PackedFloat64Array,
## rotation: Vector3i, draw_scale: float}, or {} if the node has none (a
## scene exported before the editor plugin existed).
static func origin(node: Node) -> Dictionary:
	var o = Meta.json(node, 't3_origin')
	if not (o is Dictionary) or not (o.get('location') is Array) or not (o.get('rotation') is Array):
		return {}

	var loc: Array = o['location']
	var rot: Array = o['rotation']
	return {
		'location': PackedFloat64Array([float(loc[0]), float(loc[1]), float(loc[2])]),
		'rotation': Vector3i(int(rot[0]), int(rot[1]), int(rot[2])),
		'draw_scale': float(o.get('draw_scale', 1.0)),
	}

## An actor's exported gamesys properties ({} if none).
static func gamesys(node: Node) -> Dictionary:
	var g = Meta.json(node, 't3_gamesys')
	return g if g is Dictionary else {}

## An actor's gamesys property types: {name: "float" | "byte:<Enum>" | ...}.
static func gamesys_types(node: Node) -> Dictionary:
	var t = Meta.json(node, 't3_gamesys_types')
	return t if t is Dictionary else {}

## An actor's gamesys edits from the dock ({} if none).
static func gamesys_edits(node: Node) -> Dictionary:
	var e = node.get_meta(EDITS_META, {})
	return e if e is Dictionary else {}

# --- Gamesys Values ---

## The block kind of a type string ("byte:EFoo" -> "byte").
static func base_kind(type: String) -> String:
	return type.get_slice(':', 0)

## The enum type of a type string ("byte:EFoo" -> "EFoo"), or ''.
static func enum_type(type: String) -> String:
	return type.get_slice(':', 1) if type.contains(':') else ''

## The value names of `type`'s enum, or [] if it has none.
static func enum_names(type: String, all_enums: Dictionary) -> Array:
	var names = all_enums.get(enum_type(type), [])
	return names if names is Array else []

## Whether the dock can edit property `name` of type `type` whose exported
## value is `value` (a scalar kind, and a value that was decoded as one).
static func is_editable(name: String, type: String, value: Variant) -> bool:
	if NODE_PROPERTIES.has(name):
		return false

	match base_kind(type):
		'float', 'int':
			return value is float or value is int
		'bool':
			return value is float or value is int or value is bool
		'byte':
			return value is float or value is int or (value is String and enum_type(type) != '')
		'name', 'string':
			return value is String

	return false

## `v` converted to what the edits file stores for `type`: a float, an int,
## a bool, an enum value's name (or its number if it has none), or a string.
static func normalize(type: String, v: Variant, all_enums: Dictionary = {}) -> Variant:
	match base_kind(type):
		'float':
			return float(v)
		'int':
			return int(v)
		'bool':
			return bool(v)
		'byte':
			var names := enum_names(type, all_enums)
			var i := -1
			if v is String:
				# An enum value's name stays a name; a number typed as text becomes one.
				if names.has(v):
					return v
				if not (v as String).is_valid_int():
					return v
				i = (v as String).to_int()
			else:
				i = int(v)
			if i >= 0 and i < names.size() and String(names[i]) != '':
				return String(names[i])
			return i
		'name', 'string':
			return str(v)

	return v

## Whether `a` and `b` are the same value of `type` (floats compare as the
## 32-bit floats the game stores, enums by name).
static func same_value(type: String, a: Variant, b: Variant, all_enums: Dictionary = {}) -> bool:
	if a == null or b == null:
		return a == b

	match base_kind(type):
		'float':
			return f32(float(a)) == f32(float(b))
		'int':
			return int(a) == int(b)
		'bool':
			return bool(a) == bool(b)
		'byte':
			return str(normalize(type, a, all_enums)) == str(normalize(type, b, all_enums))
		'name', 'string':
			return str(a) == str(b)

	return a == b

## `x` rounded to a 32-bit float.
static func f32(x: float) -> float:
	return PackedFloat32Array([x])[0]

# --- Changes ---

## `node`'s current placement in Unreal units and how it differs from the
## export `o` (see origin()): {location, rotation, draw_scale (current
## values), edit (the changed ones, as the edits file stores them), warnings}.
## Components that did not move keep their exported values exactly.
static func placement(node: Node3D, root: Node, o: Dictionary, upm: float) -> Dictionary:
	var edit := {}
	var warnings: Array[String] = []
	var t := level_transform(node, root)
	var expected := placement_transform(o, upm)

	# Location, per Unreal axis (Godot x, z, y).
	var loc: PackedFloat64Array = (o['location'] as PackedFloat64Array).duplicate()
	var moved := false
	for axis in 3:
		var g: int = [0, 2, 1][axis]
		var d := t.origin[g] - expected.origin[g]
		if absf(d) > LOCATION_EPS + LOCATION_REL_EPS * absf(expected.origin[g]):
			loc[axis] = roundf(t.origin[g] * upm * LOCATION_ROUND) / LOCATION_ROUND
			moved = true
	if moved:
		edit['location'] = [loc[0], loc[1], loc[2]]

	# Scale: the basis' column lengths.  T3 only has a uniform DrawScale.
	var b := t.basis
	var s0: float = o['draw_scale']
	var rot: Vector3i = o['rotation']
	var lengths := [float(b.x.length()), float(b.y.length()), float(b.z.length())]
	var s: float = (lengths[0] + lengths[1] + lengths[2]) / 3.0
	var result := {'location': loc, 'rotation': rot, 'draw_scale': s0, 'edit': edit, 'warnings': warnings}

	if s < 1e-9:
		# A zero scale has no rotation left to read.
		if absf(s0) >= 1e-9:
			warnings.append('scaled to zero; its rotation and scale are not saved')
		return result

	var mirrored := b.determinant() < 0.0
	var skewed := absf(b.x.dot(b.y)) + absf(b.y.dot(b.z)) + absf(b.z.dot(b.x)) > 1e-4 * s * s
	var uneven := absf(lengths[0] - lengths[1]) + absf(lengths[1] - lengths[2]) > 2.0 * SCALE_REL_EPS * s
	if mirrored:
		warnings.append('mirrored (negative scale); T3 cannot mirror an actor, so its rotation and scale are not saved')
		return result

	if uneven or skewed:
		warnings.append('non-uniform scale (%s, %s, %s); T3 has only a uniform DrawScale, so its scale is not saved'
			% [String.num(lengths[0], 4), String.num(lengths[1], 4), String.num(lengths[2], 4)])
	elif absf(s - s0) > SCALE_REL_EPS * maxf(absf(s0), 1e-3):
		result['draw_scale'] = roundf(s * SCALE_ROUND) / SCALE_ROUND
		edit['draw_scale'] = result['draw_scale']

	# Rotation: compare the matrices first, so float noise near pitch +-90
	# (where the angles are ill-conditioned) never reads as a change.
	var r := b.orthonormalized()
	if max_difference(r, godot_basis(rot)) > BASIS_EPS:
		var new_rot := rotator_from_basis(r, rot)
		if new_rot != rot:
			result['rotation'] = new_rot
			edit['rotation'] = [new_rot.x, new_rot.y, new_rot.z]

	return result

## `node`'s changed gamesys values, in the order of its exported properties:
## {edit: {name: value}, warnings}.  Edits equal to the exported value are
## left out.
static func gamesys_changes(node: Node, all_enums: Dictionary) -> Dictionary:
	var out := {}
	var warnings: Array[String] = []
	var edits := gamesys_edits(node)
	if edits.is_empty():
		return {'edit': out, 'warnings': warnings}

	var orig := gamesys(node)
	var types := gamesys_types(node)
	for k in orig:
		if not edits.has(k):
			continue

		var type := String(types.get(k, ''))
		if not is_editable(k, type, orig[k]):
			warnings.append('property %s cannot be edited (type %s); left out' % [k, type if type != '' else 'unknown'])
			continue

		var v = normalize(type, edits[k], all_enums)
		if not same_value(type, v, orig[k], all_enums):
			out[k] = v

	for k in edits:
		# Only an actor's own exported properties can be changed in version 1.
		if not orig.has(k):
			warnings.append('property %s is not one of its own exported properties; left out' % k)

	return {'edit': out, 'warnings': warnings}

## Everything that changed about one actor node: {edit: {location?,
## rotation?, draw_scale?, gamesys?}, placement (see placement()), warnings}.
## `edit` is empty for an untouched actor.
static func actor_changes(node: Node3D, root: Node, upm: float, all_enums: Dictionary) -> Dictionary:
	var o := origin(node)
	if o.is_empty():
		return {'edit': {}, 'placement': {}, 'no_origin': true,
			'warnings': ['has no t3_origin metadata; re-export the map with the current t3map.py']}

	var p := placement(node, root, o, upm)
	var g := gamesys_changes(node, all_enums)

	# In the edits file's order.
	var edit := {}
	for key in ['location', 'rotation', 'draw_scale']:
		if (p['edit'] as Dictionary).has(key):
			edit[key] = p['edit'][key]
	if not (g['edit'] as Dictionary).is_empty():
		edit['gamesys'] = g['edit']

	var warnings: Array[String] = []
	warnings.append_array(p['warnings'])
	warnings.append_array(g['warnings'])
	return {'edit': edit, 'placement': p, 'warnings': warnings}

## A short description of an actor's edit, e.g. "moved, rotated, 2 properties".
static func summary(edit: Dictionary) -> String:
	var parts: Array[String] = []
	if edit.has('location'):
		parts.append('moved')
	if edit.has('rotation'):
		parts.append('rotated')
	if edit.has('draw_scale'):
		parts.append('scaled')
	if edit.has('gamesys'):
		var n := (edit['gamesys'] as Dictionary).size()
		parts.append('%d propert%s' % [n, 'y' if n == 1 else 'ies'])
	return ', '.join(parts)

# --- The Level ---

## The level's actor nodes: {actors: {t3_name: node}, copies: [nodes]}.  A
## t3_name on more than one node (a duplicated actor) maps to the node the
## exporter made (see is_exported_node()), else the first in scene order; the
## others are copies, saved as new actors.
static func actor_nodes(root: Node) -> Dictionary:
	var actors := {}
	var copies: Array[Node] = []
	for n in root.find_children('*', 'Node3D', true, false):
		if not n.has_meta('t3_name'):
			continue

		var key := String(n.get_meta('t3_name'))
		if not actors.has(key):
			actors[key] = n
		elif is_exported_node(n) and not is_exported_node(actors[key]):
			# The node the exporter made is the actor; the one found first is a copy.
			copies.append(actors[key])
			actors[key] = n
		else:
			copies.append(n)

	return {'actors': actors, 'copies': copies}

## Whether `node` has the name the exporter gives an actor's node: a label,
## then " #" and the instance number of its object name ("... #1920").  A
## duplicate (Ctrl+D) is renumbered, which tells a copy from its original.
static func is_exported_node(node: Node) -> bool:
	var key := String(node.get_meta('t3_name', ''))
	var i := key.rfind('__')
	return i >= 0 and String(node.name).ends_with(' #' + key.substr(i + 2))

## Nodes added among the actors that are not T3 actors (they are not saved):
## children of the scene's folders that are neither actors nor folders.
static func foreign_nodes(root: Node) -> Array[Node]:
	var out: Array[Node] = []
	for folder in actor_folders(root):
		for c in folder.get_children():
			if not c.has_meta('t3_name') and not c.has_meta('t3_folder'):
				out.append(c)

	return out

## The scene's actor folders: the nodes marked t3_folder and, in scenes
## exported before folders existed, the group nodes in GROUPS.
static func actor_folders(root: Node) -> Array[Node]:
	var out: Array[Node] = []
	for n in root.find_children('*', '', true, false):
		if n.has_meta('t3_folder'):
			out.append(n)

	for group in GROUPS:
		var g := root.get_node_or_null(group)
		if g != null and not out.has(g):
			out.append(g)

	return out

## Classes of the actors in <Level>.actors.json next to the scene, by name,
## or {} if it is missing.
static func exported_classes(root: Node) -> Dictionary:
	var out := {}
	var path := root.scene_file_path.get_basename() + '.actors.json'
	if root.scene_file_path == '' or not FileAccess.file_exists(path):
		return out

	var doc = JSON.parse_string(FileAccess.get_file_as_string(path))
	if doc is Dictionary and doc.get('actors') is Array:
		for a in doc['actors']:
			if a is Dictionary and a.has('name'):
				out[String(a['name'])] = String(a.get('cls', ''))
	return out

## Everything that changed in the level under `root`: {doc (the edits file's
## document), changed ({key: {node, edit, summary, added?}}, for the dock's
## list), warnings, actors (the number of actor nodes), counts ({changed,
## added, removed}), not_saved ({nodes})}.
static func collect(root: Node) -> Dictionary:
	var upm := units_per_meter(root)
	var all_enums := enums(root)
	var found := actor_nodes(root)
	var nodes: Dictionary = found['actors']
	var warnings: Array[String] = []
	var changed := {}
	var actors := {}
	var no_origin: Array = []

	var names: Array = nodes.keys()
	names.sort()
	for key in names:
		var node: Node = nodes[key]
		if not (node is Node3D):
			continue

		var c := actor_changes(node as Node3D, root, upm, all_enums)
		if c.get('no_origin', false):
			no_origin.append(key)
			continue
		for w in c['warnings']:
			warnings.append('%s: %s' % [key, w])

		var edit: Dictionary = c['edit']
		if edit.is_empty():
			continue

		actors[key] = edit
		changed[key] = {'node': node, 'edit': edit, 'summary': summary(edit)}

	# New actors: copies of exported ones, where they stand and with their own
	# property edits, in scene order.
	var added: Array = []
	for node in found['copies']:
		if not (node is Node3D):
			continue

		var key := String(node.get_meta('t3_name'))
		var o := origin(node)
		if o.is_empty():
			no_origin.append(key)
			continue

		var rec := copy_record(node as Node3D, root, o, upm, all_enums)
		for w in rec['warnings']:
			warnings.append('%s (a copy of %s): %s' % [node.name, key, w])
		added.append(rec['record'])
		changed['new: %s' % root.get_path_to(node)] = {'node': node, 'edit': rec['record'],
			'summary': 'new, a copy of %s' % key, 'added': true}

	# A scene exported before the plugin existed: one warning, not one per actor.
	if not no_origin.is_empty():
		warnings.push_front('%d actor%s without t3_origin metadata (%s): exported by an older t3map.py, re-export the map'
			% [no_origin.size(), '' if no_origin.size() == 1 else 's', listed(no_origin)])

	# Removed actors: exported, and gone from the scene.  The level keeps its LevelInfo.
	var removed: Array = []
	var classes := exported_classes(root)
	for key in classes:
		if nodes.has(key):
			continue
		if String(classes[key]) == 'LevelInfo':
			warnings.append('%s: the level needs its LevelInfo, so deleting it is not saved' % key)
			continue

		removed.append(key)
		changed['removed: %s' % key] = {'node': null, 'edit': {}, 'summary': 'removed'}
	removed.sort()

	var foreign := foreign_nodes(root)
	if not foreign.is_empty():
		warnings.append(('%d node%s without T3 metadata (%s): new actors are copies of exported ones (Ctrl+D), '
			+ 'so these are not saved') % [foreign.size(), '' if foreign.size() == 1 else 's',
			listed(foreign.map(func(n): return String(n.name)))])

	# Edits still save, but the scene may lack what this plugin relies on.
	if is_outdated(root):
		warnings.push_front(('exported by older tools (export format %d, this plugin is made for %d): export it '
			+ 'again, which keeps your saved edits (Map Studio does that when you open the map from it)')
			% [export_version(root), EXPORT_VERSION])

	var doc := {'format': FORMAT, 'version': VERSION, 'level': level_name(root)}
	var src := source(root)
	if not src.is_empty():
		doc['source'] = src
	doc['actors'] = actors
	if not added.is_empty():
		doc['added'] = added
	if not removed.is_empty():
		doc['removed'] = removed
	if not foreign.is_empty():
		doc['not_saved'] = {'nodes': foreign.size()}
	return {'doc': doc, 'changed': changed, 'warnings': warnings, 'actors': nodes.size(),
		'counts': {'changed': actors.size(), 'added': added.size(), 'removed': removed.size()},
		'not_saved': {'nodes': foreign.size()}}

## The edits record of a new actor, `node`, a copy of the actor it is named
## after (origin `o`): {record: {copy_of, location, rotation, draw_scale (only
## when the copy is scaled), gamesys}, warnings}.
static func copy_record(node: Node3D, root: Node, o: Dictionary, upm: float, all_enums: Dictionary) -> Dictionary:
	var p := placement(node, root, o, upm)
	var loc: PackedFloat64Array = p['location']
	var rot: Vector3i = p['rotation']
	var rec := {'copy_of': String(node.get_meta('t3_name')), 'location': [loc[0], loc[1], loc[2]],
		'rotation': [rot.x, rot.y, rot.z]}
	if (p['edit'] as Dictionary).has('draw_scale'):
		rec['draw_scale'] = p['draw_scale']

	var gs: Dictionary = gamesys_changes(node, all_enums)['edit']
	if not gs.is_empty():
		rec['gamesys'] = gs
	return {'record': rec, 'warnings': p['warnings']}

## What an edits file could not save, from collect()'s not_saved counts:
## "3 nodes that are not T3 actors", or "" when nothing was left out.
static func not_saved_text(counts: Dictionary) -> String:
	var nodes := int(counts.get('nodes', 0))
	if nodes == 0:
		return ''

	return '%d node%s that %s not T3 actors' % [nodes, '' if nodes == 1 else 's', 'is' if nodes == 1 else 'are']

## Up to MAX_LISTED items of `items`, comma-separated, with "..." if there are more.
static func listed(items: Array) -> String:
	var shown := PackedStringArray()
	for i in mini(items.size(), MAX_LISTED):
		shown.append(str(items[i]))
	return ', '.join(shown) + (', ...' if items.size() > MAX_LISTED else '')

# --- The Edits File ---

## Where the edits of the level under `root` are saved: next to its scene,
## <Level>/<Level>.edits.json.
static func edits_path(root: Node) -> String:
	if root.scene_file_path != '':
		return root.scene_file_path.get_basename() + '.edits.json'

	var level := level_name(root)
	return 'res://%s/%s.edits.json' % [level, level]

## Collects the level's edits and writes them to `path` (default:
## edits_path()).  Returns {ok, path, actors (number saved: changed, new and
## removed), counts ({changed, added, removed}), not_saved ({nodes}),
## warnings, error}.
static func save(root: Node, path: String = '') -> Dictionary:
	if path == '':
		path = edits_path(root)

	var c := collect(root)
	var counts: Dictionary = c['counts']
	var result := {'ok': false, 'path': path,
		'actors': int(counts['changed']) + int(counts['added']) + int(counts['removed']), 'counts': counts,
		'not_saved': c['not_saved'], 'warnings': c['warnings'], 'error': ''}
	var f := FileAccess.open(path, FileAccess.WRITE)
	if f == null:
		result['error'] = 'cannot write %s (%s)' % [path, error_string(FileAccess.get_open_error())]
		return result

	f.store_string(to_json(c['doc']) + '\n')
	f.close()
	result['ok'] = true
	return result

## Reads an edits file: {doc, error}.  Checks the format and version.
static func read(path: String) -> Dictionary:
	if not FileAccess.file_exists(path):
		return {'doc': {}, 'error': 'no edits file at %s' % path}

	var doc = JSON.parse_string(FileAccess.get_file_as_string(path))
	if not (doc is Dictionary):
		return {'doc': {}, 'error': '%s is not valid JSON' % path}
	if doc.get('format') != FORMAT or not int(doc.get('version', 0)) in [1, VERSION]:
		return {'doc': {}, 'error': '%s is not a %s file of version 1 to %d' % [path, FORMAT, VERSION]}
	if not (doc.get('actors') is Dictionary):
		return {'doc': {}, 'error': '%s has no actors object' % path}

	return {'doc': doc, 'error': ''}

## What loading `doc` into the level changes: {changes, warnings}.  A change
## is {node, transform (local), gamesys (the node's new t3_gamesys_edits)},
## with create (the new node), parent and owner for a new actor, or just
## {delete: node} for a removed one.  Every actor listed in the file gets
## exactly its saved state (keys the file leaves out take their exported
## values); the other actors are left alone.  A new actor the scene already
## has (a copy standing as saved) is not made again, nor is a removed one
## that is gone already, so loading into a scene that holds the edits (an
## export applies them) changes nothing.
static func plan_load(root: Node, doc: Dictionary) -> Dictionary:
	var warnings: Array[String] = []
	var changes: Array = []
	var upm := units_per_meter(root)
	var all_enums := enums(root)
	var found := actor_nodes(root)
	var nodes: Dictionary = found['actors']

	var src := source(root)
	var file_src = doc.get('source', {})
	if file_src is Dictionary and not src.is_empty() and String(file_src.get('sha1', src['sha1'])) != src['sha1']:
		warnings.append('the edits were made for a different %s (SHA-1 %s, this scene was exported from %s)' % [
			src['file'], String(file_src.get('sha1', '')).left(12), String(src['sha1']).left(12)])

	var unknown: Array = []
	for key in doc['actors']:
		var e = doc['actors'][key]
		if not nodes.has(key) or not (e is Dictionary) or not (nodes[key] is Node3D):
			unknown.append(key)
			continue

		var node := nodes[key] as Node3D
		if origin(node).is_empty():
			warnings.append('%s has no t3_origin metadata; re-export the map with the current t3map.py' % key)
			continue

		changes.append({'node': node, 'transform': local_for_level(node, root, saved_transform(node, e, upm)),
			'gamesys': saved_gamesys(node, e, all_enums)})

	# The copies already in the scene, as the edits file records them.
	var present: Array = []
	for node in found['copies']:
		if node is Node3D and not origin(node).is_empty():
			present.append(JSON.parse_string(to_json(copy_record(node as Node3D, root, origin(node), upm,
				all_enums)['record'])))

	# New actors: copies of the actor each names, placed as saved.
	var file_added = doc.get('added', [])
	for e in (file_added if file_added is Array else []):
		var key := String(e.get('copy_of', '')) if e is Dictionary else ''
		if not nodes.has(key) or not (nodes[key] is Node3D) or origin(nodes[key]).is_empty():
			unknown.append(key)
			continue

		# Standing as saved already: each copy in the scene matches one record.
		var twin := present.find_custom(func(r): return same_json(r, e))
		if twin >= 0:
			present.remove_at(twin)
			continue

		var original := nodes[key] as Node3D
		var copy := original.duplicate() as Node3D
		copy.name = '%s (copy)' % original.name
		changes.append({'create': copy, 'parent': original.get_parent(), 'owner': root, 'node': copy,
			'transform': local_for_level(original, root, saved_transform(original, e, upm)),
			'gamesys': saved_gamesys(original, e, all_enums)})

	# Removed actors: deleted, unless they are gone already.
	var classes := exported_classes(root)
	var file_removed = doc.get('removed', [])
	for key in (file_removed if file_removed is Array else []):
		if nodes.has(String(key)):
			changes.append({'delete': nodes[String(key)]})
		elif not classes.has(String(key)):
			unknown.append(String(key))

	if not unknown.is_empty():
		warnings.append('%d actor%s in the file not found in the scene (%s)' % [unknown.size(),
			'' if unknown.size() == 1 else 's', listed(unknown)])

	return {'changes': changes, 'warnings': warnings}

## The placement an edits record `e` gives `node` (its location, rotation and
## scale, else the exported ones), relative to the level.
static func saved_transform(node: Node3D, e: Dictionary, upm: float) -> Transform3D:
	var p := origin(node).duplicate()
	if e.get('location') is Array and (e['location'] as Array).size() == 3:
		var l: Array = e['location']
		p['location'] = PackedFloat64Array([float(l[0]), float(l[1]), float(l[2])])
	if e.get('rotation') is Array and (e['rotation'] as Array).size() == 3:
		var r: Array = e['rotation']
		p['rotation'] = Vector3i(int(r[0]), int(r[1]), int(r[2]))
	if e.has('draw_scale'):
		p['draw_scale'] = float(e['draw_scale'])

	return placement_transform(p, upm)

## The gamesys edits of record `e`, typed like `node`'s exported properties.
static func saved_gamesys(node: Node, e: Dictionary, all_enums: Dictionary) -> Dictionary:
	var types := gamesys_types(node)
	var gs := {}
	var file_gs = e.get('gamesys', {})
	if file_gs is Dictionary:
		for k in file_gs:
			gs[k] = normalize(String(types.get(k, '')), file_gs[k], all_enums)

	return gs

## Applies a plan_load() or revert plan directly (the dock goes through undo/redo instead).
static func apply_changes(changes: Array) -> void:
	for c in changes:
		if c.has('delete'):
			var gone: Node = c['delete']
			gone.get_parent().remove_child(gone)
			gone.free()
			continue

		var node: Node3D = c['node']
		if c.has('create'):
			(c['parent'] as Node).add_child(node)
			node.owner = c['owner']
		node.transform = c['transform']
		if (c['gamesys'] as Dictionary).is_empty():
			node.remove_meta(EDITS_META)
		else:
			node.set_meta(EDITS_META, c['gamesys'])

## The change that puts `node` back to its exported state, or {} if it has no t3_origin.
static func revert_change(node: Node3D, root: Node) -> Dictionary:
	var o := origin(node)
	if o.is_empty():
		return {}

	return {'node': node, 'transform': local_for_level(node, root, placement_transform(o, units_per_meter(root))),
		'gamesys': {}}

## Whether two parsed JSON values are equal, numbers by value (JSON.parse_string
## returns every number as a float, while `==` on containers compares types too).
static func same_json(a: Variant, b: Variant) -> bool:
	if (a is int or a is float) and (b is int or b is float):
		return float(a) == float(b)

	if a is Dictionary and b is Dictionary:
		if a.size() != b.size():
			return false
		for k in a:
			if not b.has(k) or not same_json(a[k], b[k]):
				return false
		return true

	if a is Array and b is Array:
		if a.size() != b.size():
			return false
		for i in a.size():
			if not same_json(a[i], b[i]):
				return false
		return true

	return typeof(a) == typeof(b) and a == b

## JSON text for the edits document: objects one key per line, arrays inline,
## numbers in their shortest exact form.
static func to_json(v: Variant, indent: String = '') -> String:
	if v is Dictionary:
		if v.is_empty():
			return '{}'

		var inner := indent + '  '
		var lines := PackedStringArray()
		for k in v:
			lines.append(inner + JSON.stringify(str(k)) + ': ' + to_json(v[k], inner))
		return '{\n' + ',\n'.join(lines) + '\n' + indent + '}'

	if v is Array and (v as Array).any(func(x): return x is Dictionary):
		var inner := indent + '  '
		var rows := PackedStringArray()
		for x in v:
			rows.append(inner + to_json(x, inner))
		return '[\n' + ',\n'.join(rows) + '\n' + indent + ']'

	if v is Array or v is PackedFloat64Array:
		var items := PackedStringArray()
		for x in v:
			items.append(to_json(x, indent))
		return '[' + ', '.join(items) + ']'

	return JSON.stringify(v, '', false, true)
