extends RefCounted

## Dark UI theme for the T3 map viewer, built in code so the project needs no
## binary theme resources.  Sizes are for the 1280x720 base resolution; the
## project stretches the UI with the window ("canvas_items"), so it stays
## readable at 1440p and above.

# =============================================================================
# CONSTANTS
# =============================================================================

## Highlight colour for titles, selections and focus rings.
const ACCENT := Color(0.93, 0.62, 0.25)

## Base window background.
const BACKGROUND := Color(0.065, 0.07, 0.085)

## Semi-transparent panel fill.
const PANEL := Color(0.105, 0.115, 0.14, 0.94)

## Opaque panel fill, for panels drawn over other UI (e.g. tooltips).
const PANEL_SOLID := Color(0.105, 0.115, 0.14, 1.0)

## Fill for input fields and list rows.
const FIELD := Color(0.06, 0.066, 0.08)

## Outline colour for panels, fields and buttons.
const BORDER := Color(0.24, 0.26, 0.31)

## Primary text colour.
const TEXT := Color(0.9, 0.91, 0.93)

## Secondary/label text colour.
const TEXT_DIM := Color(0.6, 0.63, 0.68)

## Positive status colour.
const OK := Color(0.45, 0.85, 0.5)

## Warning/error status colour.
const WARN := Color(1.0, 0.45, 0.35)

# =============================================================================
# METHODS
# =============================================================================

## Builds a flat, anti-aliased style box: `color` fill, optional border and
## uniform corner radius and content margin.
static func box(color: Color, border: Color = Color(0, 0, 0, 0), border_width: int = 0, radius: int = 6,
		margin: float = 8.0) -> StyleBoxFlat:
	var s := StyleBoxFlat.new()
	s.bg_color = color
	s.border_color = border
	s.set_border_width_all(border_width)
	s.set_corner_radius_all(radius)
	s.set_content_margin_all(margin)
	s.anti_aliasing = true
	return s

## A monospace system font, trying a short list of names before falling back
## to Godot's built-in monospace font.
static func monospace(size: int = 15) -> Font:
	var f := SystemFont.new()
	f.font_names = PackedStringArray(['Cascadia Mono', 'Consolas', 'DejaVu Sans Mono', 'Menlo',
		'Liberation Mono', 'monospace'])
	f.fallbacks = [ThemeDB.fallback_font]
	return f

## Builds the viewer's dark Theme: panels, buttons, fields, trees, the
## progress bar and tooltips.
static func build() -> Theme:
	var t := Theme.new()
	t.default_font_size = 16

	t.set_stylebox('panel', 'Panel', box(PANEL, BORDER, 1, 8, 12))
	t.set_stylebox('panel', 'PanelContainer', box(PANEL, BORDER, 1, 8, 12))
	t.set_color('font_color', 'Label', TEXT)

	t.set_stylebox('normal', 'Button', box(Color(0.17, 0.185, 0.22), BORDER, 1, 6, 8))
	t.set_stylebox('hover', 'Button', box(Color(0.22, 0.24, 0.29), ACCENT.darkened(0.35), 1, 6, 8))
	t.set_stylebox('pressed', 'Button', box(ACCENT.darkened(0.3), ACCENT, 1, 6, 8))
	t.set_stylebox('hover_pressed', 'Button', box(ACCENT.darkened(0.2), ACCENT, 1, 6, 8))
	t.set_stylebox('disabled', 'Button', box(Color(0.12, 0.13, 0.15), BORDER.darkened(0.3), 1, 6, 8))
	t.set_stylebox('focus', 'Button', box(Color(0, 0, 0, 0), ACCENT, 2, 6, 8))
	t.set_color('font_color', 'Button', TEXT)
	t.set_color('font_hover_color', 'Button', Color.WHITE)
	t.set_color('font_pressed_color', 'Button', Color.WHITE)
	t.set_color('font_focus_color', 'Button', Color.WHITE)
	t.set_color('font_disabled_color', 'Button', TEXT_DIM.darkened(0.3))

	t.set_stylebox('normal', 'LineEdit', box(FIELD, BORDER, 1, 6, 8))
	t.set_stylebox('focus', 'LineEdit', box(Color(0, 0, 0, 0), ACCENT, 2, 6, 8))
	t.set_stylebox('read_only', 'LineEdit', box(FIELD, BORDER, 1, 6, 8))
	t.set_color('font_color', 'LineEdit', TEXT)
	t.set_color('font_placeholder_color', 'LineEdit', TEXT_DIM)
	t.set_color('caret_color', 'LineEdit', ACCENT)
	t.set_color('selection_color', 'LineEdit', ACCENT.darkened(0.4))

	t.set_stylebox('panel', 'Tree', box(FIELD, BORDER, 1, 6, 4))
	t.set_stylebox('focus', 'Tree', box(Color(0, 0, 0, 0), ACCENT.darkened(0.25), 1, 6, 4))
	t.set_stylebox('selected', 'Tree', box(ACCENT.darkened(0.55), Color(0, 0, 0, 0), 0, 4, 4))
	t.set_stylebox('selected_focus', 'Tree', box(ACCENT.darkened(0.35), Color(0, 0, 0, 0), 0, 4, 4))
	t.set_stylebox('hovered', 'Tree', box(Color(1, 1, 1, 0.05), Color(0, 0, 0, 0), 0, 4, 4))
	t.set_stylebox('cursor', 'Tree', StyleBoxEmpty.new())
	t.set_stylebox('cursor_unfocused', 'Tree', StyleBoxEmpty.new())
	for s in ['title_button_normal', 'title_button_hover', 'title_button_pressed']:
		t.set_stylebox(s, 'Tree', box(Color(0.13, 0.14, 0.17), BORDER, 0, 0, 6))
	t.set_color('font_color', 'Tree', TEXT)
	t.set_color('font_selected_color', 'Tree', Color.WHITE)
	t.set_color('font_hovered_color', 'Tree', Color.WHITE)
	t.set_color('title_button_color', 'Tree', TEXT_DIM)
	t.set_color('guide_color', 'Tree', Color(1, 1, 1, 0.04))
	t.set_constant('v_separation', 'Tree', 6)
	t.set_constant('h_separation', 'Tree', 10)
	t.set_constant('item_margin', 'Tree', 14)

	t.set_stylebox('background', 'ProgressBar', box(FIELD, BORDER, 1, 5, 0))
	t.set_stylebox('fill', 'ProgressBar', box(ACCENT, ACCENT, 0, 5, 0))
	t.set_color('font_color', 'ProgressBar', TEXT)

	t.set_stylebox('panel', 'TooltipPanel', box(PANEL_SOLID, BORDER, 1, 4, 6))
	t.set_color('font_color', 'TooltipLabel', TEXT)
	return t

## A label with an optional font size override and dimmed colour.
static func label(text: String = '', size: int = 0, dim: bool = false) -> Label:
	var l := Label.new()
	l.text = text
	if size > 0:
		l.add_theme_font_size_override('font_size', size)
	if dim:
		l.add_theme_color_override('font_color', TEXT_DIM)
	return l
