@tool
extends EditorPlugin

## T3 map editor: tracks the changes made to a Thief: Deadly Shadows level
## exported by tools/assets/t3map.py (actors moved, rotated or scaled with
## Godot's own gizmos, gamesys properties edited in the dock) and saves them
## as <Level>/<Level>.edits.json, the input of tools/assets/t3pack.py.
##
## Adds the "T3 Map" dock (edit_dock.gd) and Project > Tools > "Save T3
## edits" / "Load T3 edits"; saving the level's scene (Ctrl+S) saves its
## edits too.  With `-- --t3-editor-selftest <scene>` on the
## editor's command line it runs editor_selftest.gd and quits.

# =============================================================================
# VARIABLES
# =============================================================================

## The dock.
var dock: Dock

## The running in-editor self-test, if any.
var _selftest: RefCounted

# =============================================================================
# CONSTANTS
# =============================================================================

## The dock script.
const Dock := preload('res://addons/t3_map_editor/edit_dock.gd')

## The in-editor self-test script.
const EditorSelftest := preload('res://addons/t3_map_editor/editor_selftest.gd')

## Tools menu entry that saves the edits file.
const MENU_SAVE := 'Save T3 edits'

## Tools menu entry that loads the edits file.
const MENU_LOAD := 'Load T3 edits'

# =============================================================================
# METHODS
# =============================================================================

## Adds the dock and the menu entries, and follows scene, save, selection
## and undo/redo changes.
func _enter_tree() -> void:
	dock = Dock.new()
	dock.plugin = self
	add_dock(dock)
	add_tool_menu_item(MENU_SAVE, dock.save_edits)
	add_tool_menu_item(MENU_LOAD, dock.load_edits)
	scene_changed.connect(dock.on_scene_changed)
	scene_saved.connect(dock.on_scene_saved)
	EditorInterface.get_selection().selection_changed.connect(dock.on_selection_changed)
	get_undo_redo().version_changed.connect(dock.queue_refresh)

	var args := OS.get_cmdline_user_args()
	var i := args.find('--t3-editor-selftest')
	if i >= 0 and i + 1 < args.size():
		_selftest = EditorSelftest.new()
		_selftest.run.call_deferred(self, args[i + 1])

## Removes everything _enter_tree() added.
func _exit_tree() -> void:
	get_undo_redo().version_changed.disconnect(dock.queue_refresh)
	EditorInterface.get_selection().selection_changed.disconnect(dock.on_selection_changed)
	scene_saved.disconnect(dock.on_scene_saved)
	scene_changed.disconnect(dock.on_scene_changed)
	remove_tool_menu_item(MENU_SAVE)
	remove_tool_menu_item(MENU_LOAD)
	remove_dock(dock)
	dock.queue_free()
	dock = null

## The name shown in the editor.
func _get_plugin_name() -> String:
	return 'T3 Map Editor'
