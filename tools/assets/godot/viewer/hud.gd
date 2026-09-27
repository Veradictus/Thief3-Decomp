extends Control

## Viewer overlay: an info panel (map, FPS, camera position and speed, modes),
## a key hint line, a crosshair while the mouse is captured, and short
## notifications ("Lights off").  Purely visual: it never takes mouse input.

# =============================================================================
# VARIABLES
# =============================================================================

## The multi-line status text (map, FPS, position, speed, modes).
var _info: Label

## The bottom-left control hint line.
var _hint: Label

## The short-lived centred notification label.
var _toast: Label

## Seconds left to show the current toast.
var _toast_time := 0.0

## Small crosshair shown while the mouse is captured.
var _crosshair: Control

# =============================================================================
# CONSTANTS
# =============================================================================

## The shared UI theme and style helpers.
const UiTheme := preload('res://t3_tools/viewer/theme.gd')

# =============================================================================
# METHODS
# =============================================================================

## Builds the info panel, hint line, toast label and crosshair.
func _init() -> void:
	set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
	mouse_filter = Control.MOUSE_FILTER_IGNORE

	var panel := PanelContainer.new()
	panel.position = Vector2(12, 12)
	panel.mouse_filter = Control.MOUSE_FILTER_IGNORE
	panel.add_theme_stylebox_override('panel', UiTheme.box(Color(0.05, 0.055, 0.07, 0.72), UiTheme.BORDER, 1, 8, 10))
	add_child(panel)
	_info = Label.new()
	_info.add_theme_font_override('font', UiTheme.monospace())
	_info.add_theme_font_size_override('font_size', 14)
	_info.add_theme_color_override('font_color', UiTheme.TEXT)
	panel.add_child(_info)

	_hint = UiTheme.label(
		'F1 / H help  ·  hold right mouse to look  ·  C capture mouse  ·  click to inspect  ·  Esc back to maps', 14, true)
	_hint.set_anchors_and_offsets_preset(Control.PRESET_BOTTOM_LEFT)
	_hint.position += Vector2(14, -34)
	_hint.add_theme_color_override('font_outline_color', Color(0, 0, 0, 0.8))
	_hint.add_theme_constant_override('outline_size', 4)
	_hint.mouse_filter = Control.MOUSE_FILTER_IGNORE
	add_child(_hint)

	_toast = UiTheme.label('', 20)
	_toast.set_anchors_and_offsets_preset(Control.PRESET_CENTER_TOP)
	_toast.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	_toast.grow_horizontal = Control.GROW_DIRECTION_BOTH
	_toast.position.y = 18
	_toast.add_theme_color_override('font_outline_color', Color(0, 0, 0, 0.9))
	_toast.add_theme_constant_override('outline_size', 6)
	_toast.mouse_filter = Control.MOUSE_FILTER_IGNORE
	add_child(_toast)

	_crosshair = Control.new()
	_crosshair.set_anchors_and_offsets_preset(Control.PRESET_CENTER)
	_crosshair.mouse_filter = Control.MOUSE_FILTER_IGNORE
	_crosshair.draw.connect(handle_crosshair_draw)
	_crosshair.visible = false
	add_child(_crosshair)

## Sets the multi-line status text.
func set_info(text: String) -> void:
	_info.text = text

## Shows or hides the crosshair.
func set_crosshair(on: bool) -> void:
	# Avoid a redundant redraw when the state doesn't change.
	if _crosshair.visible != on:
		_crosshair.visible = on
		_crosshair.queue_redraw()

## Shows a short-lived centred notification.
func toast(text: String) -> void:
	_toast.text = text
	_toast.modulate.a = 1.0
	_toast_time = 1.6

## Draws the crosshair's four ticks with a dark outline and a light fill.
func handle_crosshair_draw() -> void:
	var c := Color(1, 1, 1, 0.85)
	var o := Color(0, 0, 0, 0.6)

	# Draw a dark outline first, then the lighter line on top.
	for w in [[o, 4.0], [c, 2.0]]:
		_crosshair.draw_line(Vector2(-10, 0), Vector2(-3, 0), w[0], w[1])
		_crosshair.draw_line(Vector2(3, 0), Vector2(10, 0), w[0], w[1])
		_crosshair.draw_line(Vector2(0, -10), Vector2(0, -3), w[0], w[1])
		_crosshair.draw_line(Vector2(0, 3), Vector2(0, 10), w[0], w[1])

## Fades out the current toast over time.
func _process(delta: float) -> void:
	if _toast_time > 0.0:
		_toast_time -= delta
		_toast.modulate.a = clampf(_toast_time / 0.4, 0.0, 1.0)
