extends SceneTree

## Headless check that exported Thief: Deadly Shadows scenes load in Godot.
##
## Usage (from the exported project folder, after `--import`):
##   godot --headless --path <project> --script res://t3_tools/check_scene.gd -- res://Inn/Inn.tscn [more scenes...]
##
## For every scene: loads it, instantiates it, and prints node, mesh, surface,
## material and texture counts plus the combined AABB. A scene with saved edits
## (<Level>.edits.json, which an export applies) must hold exactly those: the
## map editor plugin collects the same edits from it. Exits with code 1 when a
## scene fails to load, contains meshes without surfaces or does not hold its
## saved edits.

# =============================================================================
# VARIABLES
# =============================================================================

## Number of scenes that failed to load, came back with an empty mesh or do
## not hold their saved edits.
var failures := 0

# =============================================================================
# CONSTANTS
# =============================================================================

## The map editor plugin's model, which collects a scene's edits.
const EDITS_MODEL := 'res://addons/t3_map_editor/t3_edits.gd'

# =============================================================================
# METHODS
# =============================================================================

## Checks every scene path given after `--`, then exits 0 if all passed or 1
## if any failed.
func _init() -> void:
	var paths := OS.get_cmdline_user_args()
	if paths.is_empty():
		push_error('pass scene paths after --')
		quit(2)
		return

	for p in paths:
		check(p)

	quit(1 if failures > 0 else 0)

## Loads `path` as a scene, instantiates it, and prints its node, mesh,
## material and texture counts plus the combined AABB. Counts it as a failure
## if it cannot be loaded or instantiated, or contains a mesh with no surfaces.
func check(path: String) -> void:
	var res := ResourceLoader.load(path)
	if res == null or not (res is PackedScene):
		printerr('FAIL %s: could not load as PackedScene' % path)
		failures += 1
		return

	var root: Node = (res as PackedScene).instantiate()
	if root == null:
		printerr('FAIL %s: instantiate() returned null' % path)
		failures += 1
		return

	var stats := {'nodes': 0, 'mesh_instances': 0, 'surfaces': 0, 'empty_meshes': 0,
		'materials': {}, 'textures': {}, 'lights': 0}
	var aabb := AABB()
	var have_aabb := false
	var stack: Array[Node] = [root]

	while not stack.is_empty():
		var n: Node = stack.pop_back()
		stats.nodes += 1
		for c in n.get_children():
			stack.push_back(c)

		if n is Light3D:
			stats.lights += 1

		if n is MeshInstance3D:
			var mi := n as MeshInstance3D
			stats.mesh_instances += 1

			# A mesh with no surfaces has nothing to draw; count it as empty and move on.
			if mi.mesh == null or mi.mesh.get_surface_count() == 0:
				stats.empty_meshes += 1
				continue

			stats.surfaces += mi.mesh.get_surface_count()
			for s in mi.mesh.get_surface_count():
				var m := mi.get_active_material(s)

				# No material to key the count by.
				if m == null:
					continue

				stats.materials[m.resource_name if m.resource_name != '' else str(m.get_instance_id())] = true
				if m is BaseMaterial3D:
					var t := (m as BaseMaterial3D).albedo_texture
					if t != null:
						stats.textures[t.resource_path] = true

			var box := global_xform(mi) * mi.get_aabb()
			if have_aabb:
				aabb = aabb.merge(box)
			else:
				# The first mesh seeds the combined AABB.
				aabb = box
				have_aabb = true

	print(('OK %s: %d nodes, %d mesh instances, %d surfaces, %d materials, %d albedo textures, '
		+ '%d lights, %d empty meshes') % [
		path, stats.nodes, stats.mesh_instances, stats.surfaces, stats.materials.size(),
		stats.textures.size(), stats.lights, stats.empty_meshes])
	print('   AABB position %s size %s' % [aabb.position, aabb.size])

	# Any empty mesh fails the whole scene.
	if stats.empty_meshes > 0:
		failures += 1

	check_edits(path, root)
	root.free()

## Checks that the scene at `path` (instantiated as `root`) holds exactly its
## saved edits: the map editor plugin collects the same changed, new and
## removed actors from it as <Level>.edits.json lists. Scenes without an edits
## file, and projects without the plugin, are skipped.
func check_edits(path: String, root: Node) -> void:
	var file := path.get_basename() + '.edits.json'
	if not FileAccess.file_exists(file) or not ResourceLoader.exists(EDITS_MODEL):
		return

	var saved = JSON.parse_string(FileAccess.get_file_as_string(file))
	if not (saved is Dictionary):
		printerr('FAIL %s: %s is not valid JSON' % [path, file])
		failures += 1
		return

	var edits: Script = load(EDITS_MODEL)
	var got: Dictionary = JSON.parse_string(edits.to_json(edits.collect(root)['doc']))
	var differ: Array[String] = []
	for key in ['actors', 'added', 'removed']:
		var empty = {} if key == 'actors' else []
		if not edits.same_json(sorted_json(saved.get(key, empty)), sorted_json(got.get(key, empty))):
			differ.append(key)

	if differ.is_empty():
		print('   saved edits: the scene holds exactly %s' % file.get_file())
		return

	printerr('FAIL %s: the scene does not hold its saved edits (%s differ)' % [path, ', '.join(differ)])
	for key in differ:
		printerr('   %s saved %s' % [key, JSON.stringify(saved.get(key))])
		printerr('   %s found %s' % [key, JSON.stringify(got.get(key))])
	failures += 1

## `v` with an array's items in a fixed order (by their JSON text), so lists
## compare regardless of the order in which the scene holds their nodes.
func sorted_json(v: Variant) -> Variant:
	if not (v is Array):
		return v

	var items: Array = (v as Array).duplicate()
	items.sort_custom(func(a, b): return JSON.stringify(a) < JSON.stringify(b))
	return items

## `n`'s transform in world space, computed by walking its parents by hand
## since it is not yet in the tree (global_transform is not valid here).
func global_xform(n: Node3D) -> Transform3D:
	var t := n.transform
	var p := n.get_parent()

	while p != null:
		if p is Node3D:
			t = (p as Node3D).transform * t
		p = p.get_parent()

	return t
