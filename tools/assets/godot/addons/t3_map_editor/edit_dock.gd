@tool
extends EditorDock

## The "T3 Map" dock of the map editor plugin.  For an open exported level
## (<Level>/<Level>.tscn) it shows the selected actor's placement in Unreal
## units and its gamesys properties, whose scalar values can be edited here,
## and lists the changed actors (select one, revert one).  Save writes
## <Level>/<Level>.edits.json; Load applies that file to the level.  Every
## change goes through the editor's undo/redo, so Ctrl+Z works and the scene
## is marked as modified.

# =============================================================================
# VARIABLES
# =============================================================================

## The plugin, for its undo/redo manager (set before the dock is added).
var plugin: EditorPlugin

## The edited level's root, or null when the open scene is not a T3 level.
var root: Node = null

## The selected actor, or null.
var actor: Node3D = null

## The last T3Edits.collect() result's changed actors: {t3_name: {node, edit, summary}}.
var changed: Dictionary = {}

## The last T3Edits.collect() result's warnings.
var warnings: Array[String] = []

## The level name and source file.
var _level: Label

## Buttons that need an open level.
var _level_buttons: Array[Button] = []

## The selected actor's section (hidden without a selection).
var _actor_box: VBoxContainer

## Hint shown instead of the actor section.
var _hint: Label

## The selected actor's title (archetype or class).
var _actor_title: Label

## The selected actor's name.
var _actor_name: Label

## Identity and placement fields of the selected actor.
var _fields: GridContainer

## Warnings about the selected actor (non-uniform scale...).
var _actor_warning: Label

## Puts the selected actor back to its exported state.
var _revert_actor: Button

## The selected actor's gamesys properties.
var _props: Tree

## Heading of the changed-actors list.
var _edits_label: Label

## The changed actors.
var _edits: ItemList

## Reverts the actor selected in the changed-actors list.
var _revert_edit: Button

## Level-wide warnings (added or removed actors...).
var _warnings: Label

## Result of the last save or load.
var _status: Label

## Debounces refresh() after undo/redo changes.
var _timer: Timer

## Set while the properties tree is rebuilt, so item_edited is ignored.
var _building := false

# =============================================================================
# CONSTANTS
# =============================================================================

## The map editor's model.
const Edits := preload('res://addons/t3_map_editor/t3_edits.gd')

## The viewer's node-metadata reader.
const Meta := preload('res://t3_tools/viewer/t3_meta.gd')

## The viewer's inspector panel, for its value formatting.
const Inspector := preload('res://t3_tools/viewer/actor_inspector.gd')

## T3Meta.describe() fields the placement rows replace.
const HIDDEN_FIELDS := ['Position (m)', 'Position (UU)', 'Scale', 'Distance']

## Id of the revert button on a changed property's row.
const REVERT_BUTTON := 1

## Seconds to wait after an edit before collecting the level's changes again.
const REFRESH_DELAY := 0.3

## At most this many level-wide warnings are shown in the dock.
const MAX_WARNINGS := 12

# =============================================================================
# METHODS
# =============================================================================

## Builds the dock's controls.
func _init() -> void:
	title = 'T3 Map'
	default_slot = EditorDock.DOCK_SLOT_RIGHT_BL
	build_ui()

## Refreshes once the dock is in the editor.
func _ready() -> void:
	queue_refresh()

# --- Building ---

## Builds the level header, the actor section, the properties tree and the
## changed-actors list.
func build_ui() -> void:
	# Scrolls rather than claiming its full height, so the Inspector above keeps its room.
	var scroll := ScrollContainer.new()
	scroll.horizontal_scroll_mode = ScrollContainer.SCROLL_MODE_DISABLED
	add_child(scroll)
	var col := VBoxContainer.new()
	col.add_theme_constant_override('separation', 6)
	col.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	col.size_flags_vertical = Control.SIZE_EXPAND_FILL
	scroll.add_child(col)

	_level = Label.new()
	_level.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	col.add_child(_level)
	var bar := HBoxContainer.new()
	col.add_child(bar)
	bar.add_child(button('Save T3 edits', 'Write the changes to <Level>/<Level>.edits.json next to the scene',
		save_edits, true))
	bar.add_child(button('Load', "Apply <Level>/<Level>.edits.json to the level (undoable)", load_edits, true))
	bar.add_child(button('Refresh', 'Collect the changes again', refresh))
	col.add_child(HSeparator.new())

	_hint = Label.new()
	_hint.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	col.add_child(_hint)
	_actor_box = VBoxContainer.new()
	_actor_box.size_flags_vertical = Control.SIZE_EXPAND_FILL
	col.add_child(_actor_box)
	_actor_title = Label.new()
	_actor_title.theme_type_variation = &'HeaderSmall'
	_actor_title.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	_actor_box.add_child(_actor_title)
	_actor_name = Label.new()
	_actor_box.add_child(_actor_name)
	_fields = GridContainer.new()
	_fields.columns = 2
	_actor_box.add_child(_fields)
	_actor_warning = Label.new()
	_actor_warning.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	_actor_box.add_child(_actor_warning)
	_revert_actor = button('Revert actor', 'Put this actor back where it was exported and drop its property edits',
		func(): revert_actor(actor))
	_actor_box.add_child(_revert_actor)

	var props_label := Label.new()
	props_label.text = "Gameplay properties (this actor's own values)"
	_actor_box.add_child(props_label)
	_props = Tree.new()
	_props.columns = 2
	_props.hide_root = true
	_props.select_mode = Tree.SELECT_ROW
	_props.set_column_expand_ratio(0, 2)
	_props.set_column_expand_ratio(1, 3)
	_props.size_flags_vertical = Control.SIZE_EXPAND_FILL
	_props.custom_minimum_size = Vector2(0, 140)
	_props.item_edited.connect(_on_property_edited)
	_props.button_clicked.connect(_on_property_button)
	_actor_box.add_child(_props)
	col.add_child(HSeparator.new())

	var head := HBoxContainer.new()
	col.add_child(head)
	_edits_label = Label.new()
	_edits_label.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	head.add_child(_edits_label)
	_revert_edit = button('Revert', 'Put the actor selected in the list back to its exported state (a new one is '
		+ 'deleted; undo brings back a removed one)', func():
		var sel := _edits.get_selected_items()
		if not sel.is_empty():
			var e: Dictionary = changed.get(String(_edits.get_item_metadata(sel[0])), {})
			if e.get('added', false) and is_instance_valid(e['node']):
				commit_changes([{'delete': e['node']}], 'Delete new T3 actor %s' % e['node'].name)
			elif not e.is_empty():
				revert_actor(e['node']))
	head.add_child(_revert_edit)
	_edits = ItemList.new()
	_edits.custom_minimum_size = Vector2(0, 90)
	_edits.item_selected.connect(func(i: int): select_actor(String(_edits.get_item_metadata(i))))
	col.add_child(_edits)

	_warnings = Label.new()
	_warnings.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	col.add_child(_warnings)
	_status = Label.new()
	_status.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	col.add_child(_status)

	_timer = Timer.new()
	_timer.one_shot = true
	_timer.wait_time = REFRESH_DELAY
	_timer.timeout.connect(refresh)
	add_child(_timer)

## A button calling `action`; `needs_level` ones are disabled without a level.
func button(text: String, tooltip: String, action: Callable, needs_level: bool = false) -> Button:
	var b := Button.new()
	b.text = text
	b.tooltip_text = tooltip
	b.pressed.connect(func(): action.call())
	if needs_level:
		_level_buttons.append(b)
	return b

## An editor theme colour ('accent_color', 'warning_color', ...).
func color(name: String) -> Color:
	return get_theme_color(name, &'Editor')

# --- Refreshing ---

## Collects the changes again after REFRESH_DELAY (edits come in bursts).
func queue_refresh() -> void:
	if _timer.is_inside_tree():
		_timer.start()

## Called when the editor switches scenes.
func on_scene_changed(_scene_root: Node) -> void:
	refresh()

## Called when the editor saves a scene: saving the open level (Ctrl+S)
## saves its T3 edits too, so the edits file never lags behind the scene.
func on_scene_saved(path: String) -> void:
	var scene := EditorInterface.get_edited_scene_root()
	if Edits.is_level(scene) and scene.scene_file_path == path:
		save_edits()

## Called when the editor's selection changes.
func on_selection_changed() -> void:
	var picked: Node = null
	var sel := EditorInterface.get_selection().get_selected_nodes()
	if root != null and is_instance_valid(root) and not sel.is_empty():
		picked = Meta.actor_node(sel[0])

		# Only actors of the open level (not the level root itself).
		if picked != null and (picked == root or not root.is_ancestor_of(picked) or not (picked is Node3D)):
			picked = null
	actor = picked as Node3D
	show_actor()

## Finds the open level, collects its changes and updates the whole dock.
func refresh() -> void:
	var scene := EditorInterface.get_edited_scene_root()
	root = scene if Edits.is_level(scene) else null
	for b in _level_buttons:
		b.disabled = root == null

	if root == null:
		_level.text = 'Open an exported T3 level (<Level>/<Level>.tscn from tools/assets/t3map.py).'
		changed = {}
		warnings.clear()
	else:
		var src := Edits.source(root)
		_level.text = '%s  (%s%s)' % [String(root.get_meta('t3_title', Edits.level_name(root))), Edits.level_name(root),
			', ' + String(src['file']) if not src.is_empty() else '']
		var c := Edits.collect(root)
		changed = c['changed']
		warnings.assign(c['warnings'])

	fill_edits()
	on_selection_changed()

## Fills the changed-actors list and the level-wide warnings.
func fill_edits() -> void:
	_edits.clear()
	var names := changed.keys()
	names.sort()
	for key in names:
		var i := _edits.add_item('%s: %s' % [key, changed[key]['summary']])
		_edits.set_item_metadata(i, key)
		_edits.set_item_tooltip(i, Edits.to_json(changed[key]['edit']))

	_edits_label.text = 'Changed actors: %d' % changed.size()
	_revert_edit.disabled = changed.is_empty()
	var shown := warnings.slice(0, MAX_WARNINGS)
	if warnings.size() > MAX_WARNINGS:
		shown.append('... and %d more (Save lists them all in the Output panel)' % (warnings.size() - MAX_WARNINGS))
	_warnings.text = '\n'.join(shown)
	_warnings.add_theme_color_override('font_color', color('warning_color'))

# --- The Selected Actor ---

## Shows the selected actor's identity, placement and properties, or a hint.
func show_actor() -> void:
	var ok := root != null and actor != null and is_instance_valid(actor)
	_actor_box.visible = ok
	_hint.visible = not ok
	if not ok:
		_hint.text = 'Select an actor to see its placement in Unreal units and edit its properties.' if root != null else ''
		return

	var upm := Edits.units_per_meter(root)
	var info := Meta.describe({'node': actor, 'kind': 'marker', 'distance': 0.0}, upm)
	_actor_title.text = String(info['title'])
	_actor_name.text = String(info['subtitle'])
	for child in _fields.get_children():
		_fields.remove_child(child)
		child.queue_free()
	for f in info['fields']:
		if not HIDDEN_FIELDS.has(f[0]):
			add_field(String(f[0]), String(f[1]))

	var c := Edits.actor_changes(actor, root, upm, Edits.enums(root))
	var edit: Dictionary = c['edit']
	var p: Dictionary = c['placement']
	var o := Edits.origin(actor)
	if not p.is_empty():
		var loc: PackedFloat64Array = p['location']
		var rot: Vector3i = p['rotation']
		var ol: PackedFloat64Array = o['location']
		var orot: Vector3i = o['rotation']
		add_field('Location (UU)', '%.2f, %.2f, %.2f' % [loc[0], loc[1], loc[2]], edit.has('location'),
			'Exported: %s, %s, %s' % [ol[0], ol[1], ol[2]])
		add_field('Rotation', '%d, %d, %d' % [rot.x, rot.y, rot.z], edit.has('rotation'),
			'Pitch, yaw, roll in rotator units (65536 = 360 degrees): %.2f, %.2f, %.2f degrees.\nExported: %d, %d, %d'
			% [rot.x * 360.0 / 65536.0, rot.y * 360.0 / 65536.0, rot.z * 360.0 / 65536.0, orot.x, orot.y, orot.z])
		add_field('Draw scale', String.num(p['draw_scale'], 5), edit.has('draw_scale'),
			'Exported: %s' % String.num(o['draw_scale'], 5))

	_actor_warning.text = '\n'.join(c['warnings'])
	_actor_warning.visible = not (c['warnings'] as Array).is_empty()
	_actor_warning.add_theme_color_override('font_color', color('warning_color'))
	# A refused change (a non-uniform scale) is not an edit, but can be reverted.
	_revert_actor.disabled = edit.is_empty() and (c['warnings'] as Array).is_empty()
	fill_properties()

## Adds a label/value row to the actor's fields, highlighted when `changed`.
func add_field(label: String, value: String, is_changed: bool = false, tooltip: String = '') -> void:
	var k := Label.new()
	k.text = label
	k.add_theme_color_override('font_color', color('font_readonly_color'))
	_fields.add_child(k)
	var v := Label.new()
	v.text = value
	v.tooltip_text = tooltip
	v.mouse_filter = Control.MOUSE_FILTER_PASS
	v.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	v.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	if is_changed:
		v.add_theme_color_override('font_color', color('accent_color'))
	_fields.add_child(v)

## Fills the properties tree: an editor per scalar value (text, check box or
## enum list), read-only text for the rest, and a revert button on changes.
func fill_properties() -> void:
	_building = true
	_props.clear()
	var top := _props.create_item()
	var orig := Edits.gamesys(actor)
	var types := Edits.gamesys_types(actor)
	var edits := Edits.gamesys_edits(actor)
	var all_enums := Edits.enums(root)

	for k in orig:
		var type := String(types.get(k, ''))
		var value = edits.get(k, orig[k])
		var it := _props.create_item(top)
		it.set_text(0, k)
		it.set_metadata(0, k)
		it.set_tooltip_text(0, '%s (%s)' % [k, type if type != '' else 'type not exported'])

		if Edits.is_editable(k, type, orig[k]):
			set_editor(it, type, value, all_enums)
		else:
			it.set_text(1, value_text(value))
			it.set_custom_color(1, color('font_readonly_color'))
			it.set_tooltip_text(1, 'Edit it by scaling the node' if Edits.NODE_PROPERTIES.has(k)
				else 'Only scalar values can be edited here (%s)' % (type if type != '' else 'type not exported'))

		if edits.has(k) and not Edits.same_value(type, edits[k], orig[k], all_enums):
			it.set_custom_color(0, color('accent_color'))
			it.add_button(1, get_theme_icon(&'Reload', &'EditorIcons'), REVERT_BUTTON, false,
				'Revert to the exported value (%s)' % value_text(orig[k]))
	_building = false

## Sets up row `it`'s value cell as an editor for `type`.
func set_editor(it: TreeItem, type: String, value: Variant, all_enums: Dictionary) -> void:
	var names := Edits.enum_names(type, all_enums)
	match Edits.base_kind(type):
		'bool':
			it.set_cell_mode(1, TreeItem.CELL_MODE_CHECK)
			it.set_checked(1, bool(value))
			it.set_text(1, 'true' if bool(value) else 'false')
		'byte' when not names.is_empty():
			# A drop-down of the enum's names; its index is the byte value.
			var v = Edits.normalize(type, value, all_enums)
			var index: int = names.find(v) if v is String else int(v)

			# A name the enum does not list: edit it as text instead.
			if index < 0:
				it.set_cell_mode(1, TreeItem.CELL_MODE_STRING)
				it.set_text(1, str(v))
				it.set_editable(1, true)
				return

			var options := PackedStringArray()
			for i in maxi(names.size(), index + 1):
				var n := String(names[i]) if i < names.size() else ''
				options.append(n if n != '' else '(%d)' % i)
			it.set_cell_mode(1, TreeItem.CELL_MODE_RANGE)
			it.set_text(1, ','.join(options))
			it.set_range(1, index)
		_:
			it.set_cell_mode(1, TreeItem.CELL_MODE_STRING)
			it.set_text(1, edit_text(type, value))
	it.set_editable(1, true)
	it.set_tooltip_text(1, type)

## Applies what the user typed, ticked or picked in row `it` to the selected actor.
func apply_cell(it: TreeItem) -> void:
	var k := String(it.get_metadata(0))
	var type := String(Edits.gamesys_types(actor).get(k, ''))
	var value: Variant = null
	match it.get_cell_mode(1):
		TreeItem.CELL_MODE_CHECK:
			value = it.is_checked(1)
		TreeItem.CELL_MODE_RANGE:
			value = int(it.get_range(1))
		_:
			value = parse_text(type, it.get_text(1))
			if value == null:
				_status.text = '%s: "%s" is not a valid %s value' % [k, it.get_text(1), Edits.base_kind(type)]
				push_warning('T3 edits: ' + _status.text)
				show_actor.call_deferred()
				return

	set_property(actor, k, value)

## Sets gamesys property `key` of `node` to `value` through undo/redo (an edit
## back to the exported value removes the edit).  Returns false if `key`
## cannot be edited.
func set_property(node: Node, key: String, value: Variant) -> bool:
	var orig := Edits.gamesys(node)
	var type := String(Edits.gamesys_types(node).get(key, ''))
	if not orig.has(key) or not Edits.is_editable(key, type, orig[key]):
		return false

	var all_enums := Edits.enums(root) if root != null else {}
	var v = Edits.normalize(type, value, all_enums)
	var old := Edits.gamesys_edits(node)
	var new := old.duplicate()
	if Edits.same_value(type, v, orig[key], all_enums):
		new.erase(key)
	else:
		new[key] = v
	commit_gamesys(node, old, new, 'Set T3 property %s' % key)
	return true

## Replaces `node`'s gamesys edits `old` with `new` as one undoable action.
func commit_gamesys(node: Node, old: Dictionary, new: Dictionary, action: String) -> void:
	var ur := plugin.get_undo_redo()
	ur.create_action(action, UndoRedo.MERGE_DISABLE, node)
	add_meta_ops(ur, node, old, new)
	ur.commit_action()
	show_actor.call_deferred()

## Adds the do and undo steps that change `node`'s gamesys edits from `old` to `new`.
static func add_meta_ops(ur: EditorUndoRedoManager, node: Node, old: Dictionary, new: Dictionary) -> void:
	if new.is_empty():
		ur.add_do_method(node, &'remove_meta', Edits.EDITS_META)
	else:
		ur.add_do_method(node, &'set_meta', Edits.EDITS_META, new)

	if old.is_empty():
		ur.add_undo_method(node, &'remove_meta', Edits.EDITS_META)
	else:
		ur.add_undo_method(node, &'set_meta', Edits.EDITS_META, old)

## Applies T3Edits changes (see plan_load(): placements, new and removed
## actors) as one undoable action.
func commit_changes(changes: Array, action: String) -> void:
	if changes.is_empty():
		return

	var ur := plugin.get_undo_redo()
	ur.create_action(action, UndoRedo.MERGE_DISABLE, root)
	for c in changes:
		if c.has('delete'):
			var gone: Node = c['delete']
			ur.add_do_method(gone.get_parent(), &'remove_child', gone)
			ur.add_undo_method(gone.get_parent(), &'add_child', gone)
			ur.add_undo_method(gone, &'set_owner', root)
			ur.add_undo_reference(gone)
			continue

		var n: Node3D = c['node']
		if c.has('create'):
			# Not in the scene yet: placed now, then added (and taken out on undo).
			n.transform = c['transform']
			if not (c['gamesys'] as Dictionary).is_empty():
				n.set_meta(Edits.EDITS_META, c['gamesys'])
			ur.add_do_method(c['parent'], &'add_child', n)
			ur.add_do_method(n, &'set_owner', root)
			ur.add_do_reference(n)
			ur.add_undo_method(c['parent'], &'remove_child', n)
			continue

		ur.add_do_property(n, &'transform', c['transform'])
		ur.add_undo_property(n, &'transform', n.transform)
		add_meta_ops(ur, n, Edits.gamesys_edits(n), c['gamesys'])
	ur.commit_action()
	refresh()

## Puts `node` back to its exported placement and drops its property edits.
func revert_actor(node: Node3D) -> void:
	if root == null or node == null or not is_instance_valid(node):
		return

	var c := Edits.revert_change(node, root)
	if not c.is_empty():
		commit_changes([c], 'Revert T3 actor %s' % node.get_meta('t3_name'))

## Selects the actor named `key` in the editor.
func select_actor(key: String) -> void:
	var e: Dictionary = changed.get(key, {})
	var node = e.get('node')
	if node is Node and is_instance_valid(node):
		EditorInterface.get_selection().clear()
		EditorInterface.get_selection().add_node(node)
		EditorInterface.edit_node(node)

# --- Values ---

## The text a value is edited as: floats in their shortest 32-bit form.
static func edit_text(type: String, value: Variant) -> String:
	if Edits.base_kind(type) == 'float' and (value is float or value is int):
		var f := Edits.f32(float(value))
		for digits in range(0, 10):
			var s := String.num(f, digits)
			if Edits.f32(s.to_float()) == f:
				return s
		return String.num_scientific(f)

	if (Edits.base_kind(type) == 'int' or Edits.base_kind(type) == 'byte') and value is float:
		return str(int(value))

	return str(value)

## `text` parsed as a value of `type`, or null if it is not one (what the
## game can store: a finite 32-bit float, a 32-bit int, a byte, a non-empty name).
static func parse_text(type: String, text: String) -> Variant:
	var t := text.strip_edges()
	match Edits.base_kind(type):
		'float':
			var ok := t.is_valid_float() and is_finite(t.to_float()) and absf(t.to_float()) <= 3.4028234e38
			return t.to_float() if ok else null
		'int':
			var ok := t.is_valid_int() and t.to_float() >= -2147483648.0 and t.to_float() <= 2147483647.0
			return t.to_int() if ok else null
		'byte':
			return t.to_int() if t.is_valid_int() and t.to_int() >= 0 and t.to_int() <= 255 else null
		'name':
			return t if t != '' else null
	return text

## A short read-only display of any gamesys value.
static func value_text(v: Variant) -> String:
	if v is Array and Inspector.is_simple_list(v):
		return ', '.join(PackedStringArray(v.map(func(x): return Inspector.short(x))))

	if v is Array or v is Dictionary:
		var s := JSON.stringify(v)
		return s if s.length() <= 80 else s.left(77) + '...'

	return Inspector.short(v)

# --- Save and Load ---

## Writes the level's edits file; reports the result in the dock and the
## Output panel.  Returns T3Edits.save()'s result ({} without a level).
func save_edits() -> Dictionary:
	refresh()
	if root == null:
		_status.text = 'Open an exported T3 level first.'
		return {}

	var r := Edits.save(root)
	if not r['ok']:
		_status.text = 'Not saved: ' + String(r['error'])
		push_error('T3 edits: ' + String(r['error']))
		return r

	EditorInterface.get_resource_filesystem().update_file(r['path'])
	var counts: Dictionary = r['counts']
	_status.text = 'Saved %d changed, %d new and %d removed actor%s to %s' % [counts['changed'], counts['added'],
		counts['removed'], '' if r['actors'] == 1 else 's', r['path']]

	# Nodes that are not copies of exported actors cannot become actors.
	var left_out := Edits.not_saved_text(r['not_saved'])
	if left_out != '':
		_status.text += ('\nNot saved: %s. A new actor is a copy of an exported one: select it and press '
			+ 'Ctrl+D.') % left_out

	print('T3 edits: ' + _status.text)
	for w in r['warnings']:
		push_warning('T3 edits: ' + String(w))
	return r

## Applies the level's edits file to the scene as one undoable action.
## Returns {changes, warnings} or {} when there is nothing to load.
func load_edits() -> Dictionary:
	refresh()
	if root == null:
		_status.text = 'Open an exported T3 level first.'
		return {}

	var r := Edits.read(Edits.edits_path(root))
	if r['error'] != '':
		_status.text = String(r['error'])
		return {}

	var plan := Edits.plan_load(root, r['doc'])
	commit_changes(plan['changes'], 'Load T3 edits')
	var made := (plan['changes'] as Array).filter(func(c): return c.has('create')).size()
	var gone := (plan['changes'] as Array).filter(func(c): return c.has('delete')).size()
	var moved := (plan['changes'] as Array).size() - made - gone
	_status.text = 'Loaded %d changed, %d new and %d removed actor%s from %s' % [moved, made, gone,
		'' if (plan['changes'] as Array).size() == 1 else 's', Edits.edits_path(root)]
	for w in plan['warnings']:
		_status.text += '\n' + String(w)
		push_warning('T3 edits: ' + String(w))
	return plan

# --- Engine Callbacks ---

## Handles an edit in the properties tree.
func _on_property_edited() -> void:
	if not _building:
		apply_cell(_props.get_edited())

## Handles the revert button on a changed property's row.
func _on_property_button(it: TreeItem, _column: int, id: int, _mouse: int) -> void:
	if id != REVERT_BUTTON or actor == null:
		return

	var old := Edits.gamesys_edits(actor)
	var new := old.duplicate()
	new.erase(String(it.get_metadata(0)))
	commit_gamesys(actor, old, new, 'Revert T3 property %s' % it.get_metadata(0))
