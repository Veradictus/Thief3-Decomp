extends PanelContainer

## Side panel showing what T3Meta.describe() found for a picked object: the
## actor's identity, transform, mesh and material, and its gameplay (gamesys)
## properties as a tree.  Self-contained so the future map editor can reuse it:
## call show_info(info) / clear(), listen to focus_requested and closed.

# =============================================================================
# VARIABLES
# =============================================================================

## The actor/archetype title label.
var _title: Label

## The actor name/tag subtitle label.
var _subtitle: Label

## The label/value grid for the identity fields (class, mesh, position...).
var _fields: GridContainer

## The gamesys properties tree.
var _tree: Tree

## Heading shown above the properties tree, hidden when there are none.
var _props_label: Label

## The current selection's data as JSON text, for the Copy JSON button.
var _json_text := ''

# =============================================================================
# CONSTANTS
# =============================================================================

## The shared UI theme and style helpers.
const UiTheme := preload('res://t3_tools/viewer/theme.gd')

# =============================================================================
# SIGNALS
# =============================================================================

## Emitted when the user presses Focus, asking the viewer to move the camera
## to the selection.
signal focus_requested

## Emitted when the user presses the close button.
signal closed

# =============================================================================
# METHODS
# =============================================================================

## Builds the header, fields grid, properties tree and action buttons. Starts hidden.
func _init() -> void:
	custom_minimum_size = Vector2(400, 0)
	mouse_filter = Control.MOUSE_FILTER_STOP
	var col := VBoxContainer.new()
	col.add_theme_constant_override('separation', 8)
	add_child(col)

	var head := HBoxContainer.new()
	col.add_child(head)
	var names := VBoxContainer.new()
	names.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	head.add_child(names)
	_title = UiTheme.label('', 20)
	_title.add_theme_color_override('font_color', UiTheme.ACCENT)
	_title.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	names.add_child(_title)
	_subtitle = UiTheme.label('', 14, true)
	_subtitle.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	names.add_child(_subtitle)
	var close := Button.new()
	close.text = '×'
	close.tooltip_text = 'Close'
	close.focus_mode = Control.FOCUS_NONE
	close.pressed.connect(func():
		clear()
		closed.emit())
	head.add_child(close)

	_fields = GridContainer.new()
	_fields.columns = 2
	_fields.add_theme_constant_override('h_separation', 12)
	_fields.add_theme_constant_override('v_separation', 3)
	col.add_child(_fields)

	_props_label = UiTheme.label("Gameplay properties (this actor's own values)", 14, true)
	col.add_child(_props_label)
	_tree = Tree.new()
	_tree.columns = 2
	_tree.hide_root = true
	_tree.focus_mode = Control.FOCUS_NONE
	_tree.select_mode = Tree.SELECT_ROW
	_tree.set_column_expand_ratio(0, 2)
	_tree.set_column_expand_ratio(1, 3)
	_tree.size_flags_vertical = Control.SIZE_EXPAND_FILL
	_tree.custom_minimum_size = Vector2(0, 160)
	col.add_child(_tree)

	var buttons := HBoxContainer.new()
	buttons.add_theme_constant_override('separation', 8)
	col.add_child(buttons)
	var focus := Button.new()
	focus.text = 'Focus'
	focus.tooltip_text = 'Move the camera to this object'
	focus.focus_mode = Control.FOCUS_NONE
	focus.pressed.connect(func(): focus_requested.emit())
	buttons.add_child(focus)
	var copy := Button.new()
	copy.text = 'Copy JSON'
	copy.tooltip_text = "Copy this object's data to the clipboard"
	copy.focus_mode = Control.FOCUS_NONE
	copy.pressed.connect(func(): DisplayServer.clipboard_set(_json_text))
	buttons.add_child(copy)
	visible = false

## Shows `info` (as built by T3Meta.describe()): title, subtitle, identity
## fields and the gamesys properties tree.
func show_info(info: Dictionary) -> void:
	_title.text = String(info.get('title', ''))
	_subtitle.text = String(info.get('subtitle', ''))

	# Clear the previous selection's fields.
	for c in _fields.get_children():
		_fields.remove_child(c)
		c.queue_free()

	for f in info.get('fields', []):
		var k := UiTheme.label(String(f[0]), 14, true)
		k.size_flags_vertical = Control.SIZE_SHRINK_BEGIN
		_fields.add_child(k)
		var v := UiTheme.label(String(f[1]), 14)
		v.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
		v.size_flags_horizontal = Control.SIZE_EXPAND_FILL
		v.custom_minimum_size = Vector2(220, 0)
		_fields.add_child(v)

	_tree.clear()
	var root := _tree.create_item()
	var props = info.get('properties', {})
	var has_props: bool = (props is Dictionary and not props.is_empty()) or (props is Array and not props.is_empty())
	_props_label.visible = has_props
	_tree.visible = has_props
	if has_props:
		add_value(root, '', props)
	_json_text = JSON.stringify(info.get('data', {}), '  ')
	visible = true

## Hides the panel and clears the properties tree.
func clear() -> void:
	visible = false
	_tree.clear()

## Recursively adds `value` to the tree under `parent`, labelled `key` (or
## unlabelled at the root, when `key` is empty).
func add_value(parent: TreeItem, key: String, value: Variant) -> void:
	if value is Dictionary:
		var target := parent
		if key != '':
			target = _tree.create_item(parent)
			target.set_text(0, key)
			target.set_text(1, '{%d}' % value.size())
			target.set_custom_color(1, UiTheme.TEXT_DIM)
			target.collapsed = value.size() > 6
		for k in value:
			add_value(target, str(k), value[k])
	elif value is Array:
		var target := parent
		if key != '':
			target = _tree.create_item(parent)
			target.set_text(0, key)

			# Short, simple arrays are shown inline; no sub-tree needed.
			if is_simple_list(value):
				target.set_text(1, ', '.join(PackedStringArray(value.map(func(x): return short(x)))))
				target.set_tooltip_text(1, target.get_text(1))
				return

			target.set_text(1, '[%d]' % value.size())
			target.set_custom_color(1, UiTheme.TEXT_DIM)
			target.collapsed = value.size() > 6
		for i in value.size():
			var item = value[i]
			# tagged structs come as [{name, type, value}, ...]
			if item is Dictionary and item.has('name') and item.has('value'):
				add_value(target, String(item['name']), item['value'])
			else:
				add_value(target, '[%d]' % i, item)
	else:
		var it := _tree.create_item(parent)
		it.set_text(0, key)
		it.set_text(1, short(value))
		it.set_tooltip_text(1, str(value))

## Whether `a` is short enough, and free of nested structures, to show inline
## as a comma-separated line instead of its own sub-tree.
static func is_simple_list(a: Array) -> bool:
	# Too long to read comfortably on one line.
	if a.size() > 8:
		return false

	for x in a:
		# Nested structures need their own sub-tree.
		if x is Dictionary or x is Array:
			return false

	return true

## A short display string for a leaf value.
static func short(v: Variant) -> String:
	if v == null:
		return 'None'

	if v is float:
		var f: float = v
		# Whole numbers are shown without a trailing .0.
		return str(int(f)) if is_equal_approx(f, roundf(f)) and absf(f) < 1e9 else String.num(f, 4)

	if v is bool:
		return 'true' if v else 'false'

	return str(v)
