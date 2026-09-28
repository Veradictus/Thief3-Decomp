@tool
extends RefCounted

## In-editor test of the map editor plugin, started by plugin.gd when the
## editor runs with `-- --t3-editor-selftest <scene>` (godot_check.py
## --editor-selftest does this headlessly on its synthetic level):
##   godot --headless --editor --path <project> -- --t3-editor-selftest res://T3EditTest/T3EditTest.tscn
##
## Opens the level, selects actors, edits a property through the dock and
## moves an actor through the editor's undo/redo, saves with the dock's Save
## action and checks the file, then undoes, loads the file back, reverts, and
## quits the editor with 0 (pass) or 1 (fail).  The scene is never saved.

# =============================================================================
# VARIABLES
# =============================================================================

## Descriptions of failed checks.
var failures: Array[String] = []

## The editor's scene tree.
var _tree: SceneTree

# =============================================================================
# CONSTANTS
# =============================================================================

## The map editor's model.
const Edits := preload('res://addons/t3_map_editor/t3_edits.gd')

# =============================================================================
# METHODS
# =============================================================================

## Runs the test on `scene_path` with `plugin`'s dock, then quits the editor.
func run(plugin: EditorPlugin, scene_path: String) -> void:
	_tree = plugin.get_tree()
	var dock = plugin.dock
	print('T3 map editor plugin self-test')
	var root: Node = await open_level(scene_path)
	if not check(root != null, 'opens %s in the editor' % scene_path):
		finish()
		return

	dock.refresh()
	check(dock.root == root, 'the dock recognises the exported level')
	check(dock.changed.is_empty() and dock.warnings.is_empty(), 'nothing is changed after opening')

	# Selecting a node inside an actor shows that actor.
	var nodes: Dictionary = Edits.actor_nodes(root)['actors']
	var crate: Node3D = nodes['StaticMeshActor0']
	var sel := EditorInterface.get_selection()
	sel.clear()
	sel.add_node((nodes['D_100_0'] as Node).get_node('T3Light'))
	await frames(2)
	check(dock.actor == nodes['D_100_0'], "selecting a lamp's light shows the lamp actor")
	sel.clear()
	sel.add_node(crate)
	await frames(2)
	check(dock.actor == crate, 'selecting a mesh actor shows it in the dock')
	var rows := property_rows(dock)
	check(rows.size() == 11, 'the dock lists its %d gamesys properties' % rows.size())
	if rows.size() != 11:
		finish()
		return
	check(rows['Mode'].get_cell_mode(1) == TreeItem.CELL_MODE_RANGE and int(rows['Mode'].get_range(1)) == 1,
		'an enum byte is a list of names, at MODE_B')
	check(rows['bActive'].get_cell_mode(1) == TreeItem.CELL_MODE_CHECK and rows['bActive'].is_checked(1),
		'a bool is a check box')
	check(rows['Brightness'].get_text(1) == '1.2345', 'a float shows in its shortest form (%s)' % rows['Brightness'].get_text(1))
	check(not rows['Offsets'].is_editable(1) and not rows['DrawScale'].is_editable(1),
		'arrays and DrawScale are read-only')

	# Typed into the cells as the tree does: a bad byte is refused, a good int kept.
	rows['Channel'].set_text(1, '300')
	dock.apply_cell(rows['Channel'])
	check(not Edits.gamesys_edits(crate).has('Channel'), 'a byte of 300 is refused')
	check(dock.parse_text('float', 'inf') == null and dock.parse_text('float', '1e39') == null
		and dock.parse_text('name', ' ') == null and dock.parse_text('int', '-2147483648') == -2147483648,
		'values the game cannot store are refused')
	rows['Health'].set_text(1, ' 42 ')
	dock.apply_cell(rows['Health'])
	await frames(2)
	check(Edits.same_json(Edits.gamesys_edits(crate), {'Health': 42}), 'an int typed in the dock is kept as an edit')
	check(not dock.set_property(crate, 'DrawScale', 3.0), 'DrawScale is left to the node scale')

	# A move like the gizmo's, through the editor's undo/redo.
	var ur: EditorUndoRedoManager = plugin.get_undo_redo()
	var pos := crate.position
	ur.create_action('Move crate', UndoRedo.MERGE_DISABLE, crate)
	ur.add_do_property(crate, &'position', pos + Vector3(0, 0, 2))
	ur.add_undo_property(crate, &'position', pos)
	ur.commit_action()
	dock.refresh()
	var summary := String(dock.changed.get('StaticMeshActor0', {}).get('summary', ''))
	check(dock.changed.size() == 1 and summary == 'moved, 1 property', 'the changed list shows "%s"' % summary)

	# Save: two metres along Godot +Z is Unreal +Y.
	var r: Dictionary = dock.save_edits()
	var doc = JSON.parse_string(FileAccess.get_file_as_string(String(r.get('path', ''))))
	var y := roundf((-250.25 + 2.0 * Edits.units_per_meter(root)) * 100.0) / 100.0
	var want := {'StaticMeshActor0': {'location': [100.5, y, 32.0], 'gamesys': {'Health': 42}}}
	check(doc is Dictionary and Edits.same_json(doc.get('actors'), want),
		'Save T3 edits wrote the move and the property: %s' % JSON.stringify(doc.get('actors') if doc is Dictionary else doc))

	# Undo both, then load the file back and revert from the dock.
	var history := ur.get_history_undo_redo(ur.get_object_history_id(crate))
	history.undo()
	history.undo()
	dock.refresh()
	check(dock.changed.is_empty(), 'undo takes both changes back')
	var plan: Dictionary = dock.load_edits()
	check((plan.get('changes', []) as Array).size() == 1 and dock.changed.size() == 1
		and Edits.same_json(dock.changed['StaticMeshActor0']['edit'], want['StaticMeshActor0']),
		'Load T3 edits restores the saved changes')
	dock.revert_actor(crate)
	check(dock.changed.is_empty(), 'Revert actor puts it back as exported')
	history.undo()
	dock.refresh()
	check(dock.changed.size() == 1, 'and undo brings the change back')

	# Saving the scene (Ctrl+S) writes the edits file too. The signal stands in
	# for a real save, which fails headless (no viewport for the thumbnail).
	var edits_path := String(r.get('path', ''))
	DirAccess.remove_absolute(ProjectSettings.globalize_path(edits_path))
	plugin.scene_saved.emit(root.scene_file_path)
	await frames(2)
	doc = JSON.parse_string(FileAccess.get_file_as_string(edits_path))
	check(doc is Dictionary and Edits.same_json(doc.get('actors'), want), 'saving the scene saves the T3 edits too')

	# A duplicate (Ctrl+D) saves as a new actor; loading the file into a scene
	# without it makes the copy again, and undo takes it away.
	var copy := crate.duplicate() as Node3D
	crate.get_parent().add_child(copy)
	copy.owner = root
	copy.position += Vector3(3, 0, 0)
	r = dock.save_edits()
	doc = JSON.parse_string(FileAccess.get_file_as_string(String(r.get('path', ''))))
	var added: Array = doc.get('added', []) if doc is Dictionary else []
	check(added.size() == 1 and String(added[0].get('copy_of')) == 'StaticMeshActor0',
		'a duplicate is saved as a new actor: %s' % JSON.stringify(added))
	copy.get_parent().remove_child(copy)
	copy.free()
	dock.load_edits()
	var copies: Array = Edits.actor_nodes(root)['copies']
	check(copies.size() == 1, 'Load T3 edits makes the new actor again')
	history.undo()
	dock.refresh()
	check((Edits.actor_nodes(root)['copies'] as Array).is_empty(), 'and undo takes it away')

	finish()

## Opens `path` once the editor has started up (it opens the main scene or the
## last session's scenes itself) and waits until it stays the edited scene.
## Returns its root, or null if that does not happen within 1200 frames.
func open_level(path: String) -> Node:
	var fs := EditorInterface.get_resource_filesystem()
	var steady := 0
	for i in 1200:
		var root := EditorInterface.get_edited_scene_root()
		if root != null and root.scene_file_path == path:
			steady += 1
			if steady >= 30:
				return root
		elif not fs.is_scanning():
			steady = 0
			EditorInterface.open_scene_from_path(path)
		await frames(1)
	return null

## The dock's property rows by name.
func property_rows(dock: Node) -> Dictionary:
	var rows := {}
	var top: TreeItem = dock._props.get_root()
	if top != null:
		for it in top.get_children():
			rows[it.get_text(0)] = it
	return rows

## Prints a pass/fail line for one check and records failures.
func check(ok: bool, what: String) -> bool:
	print(('  ok    ' if ok else '  FAIL  ') + what)
	if not ok:
		failures.append(what)
	return ok

## Waits `n` frames.
func frames(n: int) -> void:
	for i in n:
		await _tree.process_frame

## Prints the result and quits the editor with 0 (pass) or 1 (fail).
func finish() -> void:
	if failures.is_empty():
		print('EDITOR SELFTEST PASSED')
	else:
		print('EDITOR SELFTEST FAILED: ' + ', '.join(failures))
	_tree.quit(0 if failures.is_empty() else 1)
