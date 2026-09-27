extends RefCounted

## Reads the T3 metadata the exporter stores on scene nodes and turns a pick
## result into something an inspector can show.
##
## Actor nodes (instances in StaticMeshes, lights, markers) carry t3_name,
## t3_class, t3_archetype, t3_base, t3_mesh, t3_skin, t3_tag, t3_attached_to,
## t3_attached_bone, t3_gamesys (JSON), t3_light (JSON).  Nodes and materials
## inside the exported .glb files carry glTF "extras" (t3_mesh, t3_block_id,
## t3_material, stages, category...).

# =============================================================================
# METHODS
# =============================================================================

## The node carrying the actor metadata for `node` (itself or an ancestor).
static func actor_node(node: Node) -> Node:
	var cur := node
	while cur != null:
		if cur.has_meta('t3_name'):
			return cur
		cur = cur.get_parent()
	return null

## Reads and JSON-decodes the metadata under `key` on `node`. Returns the raw
## value if it isn't a JSON-encoded string, or null if `key` isn't set.
static func json(node: Node, key: String) -> Variant:
	if not node.has_meta(key):
		return null

	var raw = node.get_meta(key)
	if raw is String:
		var parsed = JSON.parse_string(raw)
		return parsed if parsed != null else raw
	return raw

## Formats `v`'s three components with `digits` decimal places, comma-separated.
static func fmt_vec(v: Vector3, digits: int = 2) -> String:
	var f := '%.' + str(digits) + 'f'
	return (f + ', ' + f + ', ' + f) % [v.x, v.y, v.z]

## Unreal-space coordinates for a Godot position (the exporter swaps Y and Z).
static func to_unreal(p: Vector3, units_per_meter: float) -> Vector3:
	return Vector3(p.x, p.z, p.y) * units_per_meter

## `hit` is a result of T3Pick.pick().  Returns
## {title, subtitle, fields: [[label, value]...], properties, target (Node3D), data (for JSON export)}.
static func describe(hit: Dictionary, units_per_meter: float) -> Dictionary:
	var node: Node = hit.get('node')
	var info := {'title': '', 'subtitle': '', 'fields': [], 'properties': {}, 'target': node, 'data': {}}
	if node == null:
		return info

	var fields: Array = info['fields']
	var data: Dictionary = info['data']
	var actor := actor_node(node)

	if actor != null:
		# An actor's own node (mesh instance, light or marker) carries the t3_* metadata.
		var cls := String(actor.get_meta('t3_class', ''))
		var arche := String(actor.get_meta('t3_archetype', ''))
		info['title'] = arche if arche != '' else cls
		info['subtitle'] = String(actor.get_meta('t3_name', actor.name))
		info['target'] = actor
		for pair in [['Class', 't3_class'], ['Base class', 't3_base'], ['Archetype', 't3_archetype'],
				['Mesh', 't3_mesh'], ['Skin', 't3_skin'], ['Tag', 't3_tag'],
				['Attached to', 't3_attached_to'], ['Attach bone', 't3_attached_bone']]:
			if actor.has_meta(pair[1]) and String(actor.get_meta(pair[1])) != '':
				fields.append([pair[0], String(actor.get_meta(pair[1]))])
				data[pair[1].trim_prefix('t3_')] = String(actor.get_meta(pair[1]))

		if actor.get_meta('t3_default_start', false):
			fields.append(['Player start', 'default'])

		if actor is Node3D:
			var n3 := actor as Node3D
			var p := n3.global_position
			fields.append(['Position (m)', fmt_vec(p)])
			fields.append(['Position (UU)', fmt_vec(to_unreal(p, units_per_meter), 1)])
			var s := n3.global_transform.basis.get_scale()

			# Only worth a field away from the default scale.
			if not s.is_equal_approx(Vector3.ONE):
				fields.append(['Scale', '%.3f' % s.x])

			data['position_m'] = [p.x, p.y, p.z]

		var gamesys = json(actor, 't3_gamesys')
		if gamesys != null:
			info['properties'] = gamesys
			data['gamesys'] = gamesys

		var light = json(actor, 't3_light')
		if light is Dictionary:
			var l: Dictionary = light
			fields.append(['Light', '%s, brightness %s, radius %s' % [l.get('flesh_type', l.get('kind', '?')),
				l.get('brightness', '?'), l.get('radius', '?')]])
			data['light'] = l
	else:
		# No actor metadata: a BSP block (glTF extras carry its block id) or another raw glTF node.
		var extras = node.get_meta('extras', null)
		if extras is Dictionary and extras.has('t3_block_id'):
			info['title'] = 'BSP block'
			info['subtitle'] = '%s (block id %d)' % [node.name, int(extras['t3_block_id'])]
			data['bsp_block_id'] = int(extras['t3_block_id'])
		else:
			info['title'] = node.get_class()
			info['subtitle'] = String(node.name)
		info['target'] = node

	# The surface under the ray: material and its texture stages.
	if hit.get('kind', '') == 'mesh' and node is MeshInstance3D and hit.has('surface'):
		var mat := (node as MeshInstance3D).get_active_material(int(hit['surface']))
		if mat != null:
			fields.append(['Material', mat.resource_name if mat.resource_name != '' else '(unnamed)'])
			var mx = mat.get_meta('extras', null)
			if mx is Dictionary:
				var stages: Array[String] = []
				for st in mx.get('stages', []):
					if String(st) != '':
						stages.append(String(st))
				if not stages.is_empty():
					fields.append(['Textures', ', '.join(stages)])
				if String(mx.get('category', '')) != '':
					fields.append(['Surface', String(mx['category'])])
				data['material'] = mx

	if node is MeshInstance3D:
		var ex = node.get_meta('extras', null)

		# Alternate skins are only meaningful for an actor's own mesh instance.
		if ex is Dictionary and ex.has('t3_skins') and actor != null:
			fields.append(['Skins', ', '.join(PackedStringArray(ex['t3_skins']))])

	fields.append(['Distance', '%.2f m' % float(hit.get('distance', 0.0))])
	data['title'] = info['title']
	data['name'] = info['subtitle']
	return info
