extends Control

## Map picker: lists the exported maps, filters them, and loads the chosen one
## in the background (ResourceLoader threaded load) before switching to the
## viewer.  Keyboard: type to filter, Up/Down/PageUp/PageDown to move, Enter to
## load, Esc to clear the filter.  Mouse: double-click a map.

# =============================================================================
# VARIABLES
# =============================================================================

## The map name/file filter box.
var _filter: LineEdit

## The map list.
var _tree: Tree

## "N of M maps" counter, next to the filter box.
var _count: Label

## Details line for the selected map (scene path, actor/mesh/light counts, default start).
var _details: Label

## The "Load map" button.
var _load_button: Button

## Container for the loading progress bar and its label, hidden until a load starts.
var _progress_box: VBoxContainer

## The loading progress bar.
var _progress: ProgressBar

## Label above the progress bar ("Loading <map>…  N%").
var _progress_label: Label

## Resource path currently being loaded in the background, or '' when idle.
var _loading_path := ''

## The map entry currently being loaded.
var _loading_entry: Dictionary = {}

## Time.get_ticks_msec() when the current load started, for the elapsed-time readout.
var _load_started_ms := 0

## Whether _ready() has finished building the UI (see is_ready()).
var _ready_done := false

# =============================================================================
# CONSTANTS
# =============================================================================

## The shared UI theme and style helpers.
const UiTheme := preload('res://t3_tools/viewer/theme.gd')

# =============================================================================
# METHODS
# =============================================================================

## Builds the UI, loads the map list, and either jumps straight into a map or
## takes a picker screenshot if asked to on the command line.
func _ready() -> void:
	theme = UiTheme.build()
	set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
	build()
	T3Viewer.refresh_maps()
	_filter.text = T3Viewer.last_filter
	populate()
	_filter.grab_focus.call_deferred()
	_ready_done = true

	var auto := String(T3Viewer.options.get('map', ''))

	# --t3-map was given: load it directly, unless a self-test drives the picker itself.
	if auto != '' and not T3Viewer.options.has('selftest') and T3Viewer.current.is_empty():
		var entry: Dictionary = T3Viewer.find_map(auto)
		if not entry.is_empty():
			start_load(entry)
	elif auto == '' and T3Viewer.options.has('screenshot') and not T3Viewer.options.has('selftest'):
		screenshot_and_quit(String(T3Viewer.options['screenshot']))

## Whether _ready() has finished building the UI.
func is_ready() -> bool:
	return _ready_done

# --- UI ---

## Builds the background, title, filter row, map list, details line, progress
## bar and buttons.
func build() -> void:
	var bg := ColorRect.new()
	bg.color = UiTheme.BACKGROUND
	bg.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
	add_child(bg)

	var margin := MarginContainer.new()
	margin.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
	for side in ['left', 'right']:
		margin.add_theme_constant_override('margin_' + side, 64)
	margin.add_theme_constant_override('margin_top', 40)
	margin.add_theme_constant_override('margin_bottom', 32)
	add_child(margin)

	var col := VBoxContainer.new()
	col.add_theme_constant_override('separation', 12)
	margin.add_child(col)

	var title := UiTheme.label(T3Viewer.APP_TITLE, 34)
	title.add_theme_color_override('font_color', UiTheme.ACCENT)
	col.add_child(title)
	col.add_child(UiTheme.label('Maps exported from your own copy of the game by tools/assets/t3map.py.', 15, true))

	var row := HBoxContainer.new()
	row.add_theme_constant_override('separation', 12)
	col.add_child(row)
	_filter = LineEdit.new()
	_filter.placeholder_text = 'Filter maps by name or file…'
	_filter.clear_button_enabled = true
	_filter.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	_filter.text_changed.connect(func(_t): populate())
	_filter.text_submitted.connect(func(_t): handle_load_selected())
	_filter.gui_input.connect(handle_filter_input)
	row.add_child(_filter)
	_count = UiTheme.label('', 15, true)
	row.add_child(_count)

	_tree = Tree.new()
	_tree.columns = 3
	_tree.hide_root = true
	_tree.column_titles_visible = true
	_tree.set_column_title(0, 'Map')
	_tree.set_column_title(1, 'File')
	_tree.set_column_title(2, 'Actors')
	_tree.set_column_expand(0, true)
	_tree.set_column_expand_ratio(0, 3)
	_tree.set_column_expand(1, true)
	_tree.set_column_expand_ratio(1, 2)
	_tree.set_column_expand(2, false)
	_tree.set_column_custom_minimum_width(2, 90)
	_tree.select_mode = Tree.SELECT_ROW
	_tree.size_flags_vertical = Control.SIZE_EXPAND_FILL
	_tree.item_activated.connect(handle_load_selected)
	_tree.item_selected.connect(update_details)
	col.add_child(_tree)

	_details = UiTheme.label('', 15, true)
	_details.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	col.add_child(_details)

	_progress_box = VBoxContainer.new()
	_progress_box.visible = false
	col.add_child(_progress_box)
	_progress_label = UiTheme.label('', 16)
	_progress_box.add_child(_progress_label)
	_progress = ProgressBar.new()
	_progress.min_value = 0.0
	_progress.max_value = 100.0
	_progress.custom_minimum_size = Vector2(0, 22)
	_progress_box.add_child(_progress)

	var buttons := HBoxContainer.new()
	buttons.add_theme_constant_override('separation', 12)
	col.add_child(buttons)
	_load_button = Button.new()
	_load_button.text = 'Load map'
	_load_button.custom_minimum_size = Vector2(140, 0)
	_load_button.pressed.connect(handle_load_selected)
	buttons.add_child(_load_button)
	var quit := Button.new()
	quit.text = 'Quit'
	quit.pressed.connect(func(): get_tree().quit())
	buttons.add_child(quit)
	var spacer := Control.new()
	spacer.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	buttons.add_child(spacer)
	buttons.add_child(UiTheme.label(
		'Type to filter · Up/Down to choose · Enter or double-click to load · F1 or H in a map for help', 14, true))

## Saves a frame of the picker to `path` and quits, for --t3-screenshot with no map.
func screenshot_and_quit(path: String) -> void:
	for i in int(T3Viewer.options.get('frames', '10')):
		await get_tree().process_frame
	await RenderingServer.frame_post_draw
	var err := get_viewport().get_texture().get_image().save_png(path)
	print('screenshot %s: %s' % [path, 'saved' if err == OK else 'error %d' % err])
	get_tree().quit(0 if err == OK else 1)

# --- Map List ---

## Refills the tree from T3Viewer.maps, applying the current filter text and
## keeping the previously-selected map selected if it still matches.
func populate() -> void:
	T3Viewer.last_filter = _filter.text
	_tree.clear()
	var root := _tree.create_item()
	var needle := _filter.text.strip_edges().to_lower()
	var shown := 0
	var to_select: TreeItem = null

	for entry in T3Viewer.maps:
		var title: String = T3Viewer.map_title(entry)
		var id := String(entry.get('id', ''))

		# Skip maps that don't match the filter text.
		if needle != '' and not (title.to_lower().contains(needle) or id.to_lower().contains(needle)):
			continue

		var item := _tree.create_item(root)
		item.set_text(0, title)
		item.set_text(1, id)
		item.set_text(2, count_text(entry.get('actors', '')))
		item.set_text_alignment(2, HORIZONTAL_ALIGNMENT_RIGHT)
		item.set_custom_color(1, UiTheme.TEXT_DIM)
		item.set_custom_color(2, UiTheme.TEXT_DIM)
		item.set_metadata(0, entry)

		# Keep the previous selection if it is still in the filtered list.
		if to_select == null or id == T3Viewer.last_selected:
			to_select = item

		shown += 1

	_count.text = '%d of %d maps' % [shown, T3Viewer.maps.size()]

	# An empty project: tell the user how to fill it.
	if T3Viewer.maps.is_empty():
		_details.text = 'No exported maps found in this project. Run: python tools/assets/t3map.py --all'

	if to_select != null:
		to_select.select(0)
		_tree.scroll_to_item(to_select)

	update_details()
	_load_button.disabled = to_select == null or _loading_path != ''

## Updates the details line for the currently selected map.
func update_details() -> void:
	var item := _tree.get_selected()
	if item == null:
		if not T3Viewer.maps.is_empty():
			_details.text = 'No map matches the filter.'
		return

	var e: Dictionary = item.get_metadata(0)
	var parts: Array[String] = [String(e.get('scene', ''))]
	if e.has('actors'):
		parts.append('%s actors' % count_text(e['actors']))
	if e.has('meshes'):
		parts.append('%s mesh/skin files' % count_text(e['meshes']))
	if e.has('lights'):
		parts.append('%s lights' % count_text(e['lights']))
	if String(e.get('default_start', '')) != '':
		parts.append('start: ' + String(e['default_start']))

	_details.text = ' · '.join(parts)

## JSON numbers arrive as floats; show counts as integers.
static func count_text(v: Variant) -> String:
	if v is float or v is int:
		return str(int(v))
	return str(v)

# --- Input ---

## Keyboard navigation: Up/Down/PageUp/PageDown to move, Esc to clear the filter.
func handle_filter_input(event: InputEvent) -> void:
	if not (event is InputEventKey and event.pressed):
		return

	var key := (event as InputEventKey).keycode
	var step := 0
	match key:
		KEY_UP:
			step = -1
		KEY_DOWN:
			step = 1
		KEY_PAGEUP:
			step = -10
		KEY_PAGEDOWN:
			step = 10
		KEY_ESCAPE:
			if _filter.text != '':
				_filter.text = ''
				populate()
			_filter.accept_event()
			return

	if step != 0:
		move_selection(step)
		_filter.accept_event()

## Moves the tree selection by `step` rows, clamped to the visible list.
func move_selection(step: int) -> void:
	var items: Array[TreeItem] = []
	var root := _tree.get_root()
	if root == null:
		return

	var it := root.get_first_child()
	while it != null:
		items.append(it)
		it = it.get_next()

	if items.is_empty():
		return

	var cur := items.find(_tree.get_selected())
	var nxt := clampi((0 if cur < 0 else cur) + step, 0, items.size() - 1)
	items[nxt].select(0)
	_tree.scroll_to_item(items[nxt])

# --- Loading ---

## Starts loading the selected map, if any and none is already loading.
func handle_load_selected() -> void:
	var item := _tree.get_selected()
	if item == null or _loading_path != '':
		return
	start_load(item.get_metadata(0))

## Starts the background load of a map entry.  Also used by the self-test.
func start_load(entry: Dictionary) -> void:
	if _loading_path != '':
		return

	var path := String(entry.get('scene', ''))

	# Sub-threads load the map's many mesh files in parallel.  The headless
	# (dummy) renderer is not safe for that, so scripted headless runs use one
	# loader thread.
	var sub_threads := DisplayServer.get_name() != 'headless'
	var err := ResourceLoader.load_threaded_request(path, 'PackedScene', sub_threads)
	if err != OK:
		show_error('Could not start loading %s (error %d).' % [path, err])
		return

	_loading_entry = entry
	_loading_path = path
	_load_started_ms = Time.get_ticks_msec()
	_progress_box.visible = true
	_progress.value = 0.0
	_progress_label.text = 'Loading %s…' % T3Viewer.map_title(entry)
	_load_button.disabled = true
	_filter.editable = false
	_tree.mouse_filter = Control.MOUSE_FILTER_IGNORE

## Shows `text` as an error in the progress area and re-enables the UI.
func show_error(text: String) -> void:
	_progress_box.visible = true
	_progress_label.text = text
	_progress_label.add_theme_color_override('font_color', UiTheme.WARN)
	_load_button.disabled = false
	_filter.editable = true
	_tree.mouse_filter = Control.MOUSE_FILTER_STOP
	push_error(text)

# --- Engine Callbacks ---

## Polls the threaded load and hands the scene to the viewer once it's ready.
func _process(_delta: float) -> void:
	if _loading_path == '':
		return

	var progress := []
	var status := ResourceLoader.load_threaded_get_status(_loading_path, progress)
	match status:
		ResourceLoader.THREAD_LOAD_IN_PROGRESS:
			var pct := 100.0 * float(progress[0]) if progress.size() > 0 else 0.0
			_progress.value = pct
			_progress_label.text = 'Loading %s…  %d%%  (%.1f s)' % [T3Viewer.map_title(_loading_entry), int(pct),
				(Time.get_ticks_msec() - _load_started_ms) / 1000.0]
		ResourceLoader.THREAD_LOAD_LOADED:
			var scene := ResourceLoader.load_threaded_get(_loading_path) as PackedScene
			var entry := _loading_entry
			_loading_path = ''

			if scene == null:
				show_error('%s did not load as a scene.' % entry.get('scene', '?'))
				return

			_progress.value = 100.0
			_progress_label.text = 'Building the scene…'
			T3Viewer.open_viewer(entry, scene)
		_:
			var path := _loading_path
			_loading_path = ''
			show_error('Loading %s failed (status %d). Re-import the project in Godot, or re-run t3map.py.' % [path, status])
