extends PanelContainer

## Controls reference (F1 / H).  Key names come from the live input map, so
## the overlay stays correct if the bindings are changed in project settings.

# =============================================================================
# CONSTANTS
# =============================================================================

## The shared UI theme and style helpers.
const UiTheme := preload('res://t3_tools/viewer/theme.gd')

## [description, action or literal text]; literal entries start with '='.
const ROWS := [
	['Move forward / back / left / right', 't3_move_forward|t3_move_back|t3_move_left|t3_move_right'],
	['Move down / up', 't3_move_down|t3_move_up'],
	['Look around', '=Hold right mouse button'],
	['Capture / release the mouse (look without holding)', 't3_toggle_capture'],
	['Fast / slow', 't3_fast|t3_slow'],
	['Base speed up / down', '=Mouse wheel'],
	['Inspect the object under the cursor / crosshair', 't3_select|t3_inspect'],
	['Focus the camera on the selection', 't3_focus'],
	['Next player start', 't3_next_start'],
	['View: lit / unlit / wireframe / cycle', 't3_view_lit|t3_view_unlit|t3_view_wireframe|t3_view_cycle'],
	["Lamps (the map's own lights) on / off", 't3_toggle_lights'],
	['Lighting: editor (with preview sun) / game / flat', 't3_cycle_lighting'],
	['Markers (starts, AI points, lights, sounds...)', 't3_toggle_markers'],
	['This help', 't3_help'],
	['Release the mouse, then back to the map list', 't3_back'],
]

# =============================================================================
# METHODS
# =============================================================================

## Builds the two-column key/action grid from ROWS. Starts hidden.
func _init() -> void:
	mouse_filter = Control.MOUSE_FILTER_STOP
	var col := VBoxContainer.new()
	col.add_theme_constant_override('separation', 10)
	add_child(col)

	var title := UiTheme.label('Controls', 24)
	title.add_theme_color_override('font_color', UiTheme.ACCENT)
	col.add_child(title)

	var grid := GridContainer.new()
	grid.columns = 2
	grid.add_theme_constant_override('h_separation', 28)
	grid.add_theme_constant_override('v_separation', 6)
	col.add_child(grid)

	for row in ROWS:
		grid.add_child(UiTheme.label(row[0], 16))
		var keys := String(row[1])

		# A '=' prefix means literal text, not an action name.
		var text := keys.substr(1) if keys.begins_with('=') else keys_text(keys)

		var k := UiTheme.label(text, 16)
		k.add_theme_color_override('font_color', UiTheme.ACCENT.lightened(0.25))
		grid.add_child(k)

	col.add_child(UiTheme.label('Speeds are in metres per second. Esc also closes this panel.', 14, true))
	visible = false

## Centres the panel in its parent (needs the control to be in the tree first).
func _ready() -> void:
	set_anchors_and_offsets_preset(Control.PRESET_CENTER)
	grow_horizontal = Control.GROW_DIRECTION_BOTH
	grow_vertical = Control.GROW_DIRECTION_BOTH

## Combines the key hints for a `|`-separated list of action names, e.g. 'W / Up'.
func keys_text(actions: String) -> String:
	var parts: Array[String] = []
	for a in actions.split('|'):
		parts.append(T3Viewer.action_keys(a))
	return '   '.join(parts)
