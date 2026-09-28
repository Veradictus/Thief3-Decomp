extends SceneTree

## Headless test of the map editor's model (t3_edits.gd) on the synthetic
## level that `godot_check.py --editor-selftest` writes (made-up actors, no
## game data).
##
## Usage (from the project folder, after --import):
##   godot --headless --path <project> --script res://addons/t3_map_editor/selftest.gd -- res://T3EditTest/T3EditTest.tscn [res://T3EditBaked/T3EditBaked.tscn]
##
## Checks the rotator round trip (godot_basis() then rotator_from_basis(),
## including pitch +-90 and rotators outside the canonical range), that the
## untouched level has no edits, then moves, rotates and scales actors and
## edits gamesys values, saves with the same code as the dock's Save button,
## and compares the file with the expected values; then loads the file into a
## fresh copy of the level and checks that it collects the same edits.  The
## optional second scene is the level exported with saved edits: loading them
## into it again must change nothing.  Exits with 0 (pass) or 1 (fail).

# =============================================================================
# VARIABLES
# =============================================================================

## Descriptions of failed checks.
var failures: Array[String] = []

# =============================================================================
# CONSTANTS
# =============================================================================

## The model under test.
const Edits := preload('res://addons/t3_map_editor/t3_edits.gd')

## Actors the synthetic level must keep out of the edits file.
const UNTOUCHED := ['LevelInfo0', 'StaticMeshActor1', 'D_100_0', 'PlayerStart0', 'Near_Gimbal', 'Far']

# =============================================================================
# METHODS
# =============================================================================

## Runs every check on the scene given after `--`, then quits with 0 or 1.
func _init() -> void:
	var args := OS.get_cmdline_user_args()
	if args.is_empty():
		push_error('pass the synthetic level scene after --')
		quit(2)
		return

	print('T3 map editor model self-test')
	test_rotators()
	var packed := load(args[0]) as PackedScene
	if not check(packed != null, 'loads %s' % args[0]):
		quit(1)
		return

	test_untouched(packed)
	var saved := test_edits(packed)
	if not saved.is_empty():
		test_load(packed, saved)
	test_load_added(packed)
	test_speed()
	test_old_export(packed)
	if args.size() > 1:
		test_saved_export(args[1])

	if failures.is_empty():
		print('SELFTEST PASSED')
		quit(0)
	else:
		print('SELFTEST FAILED: ' + ', '.join(failures))
		quit(1)

## Prints a pass/fail line for one check and records failures.
func check(ok: bool, what: String) -> bool:
	print(('  ok    ' if ok else '  FAIL  ') + what)
	if not ok:
		failures.append(what)
	return ok

## The actor node named `t3_name` under `root`.
func actor(root: Node, t3_name: String) -> Node3D:
	return Edits.actor_nodes(root)['actors'].get(t3_name) as Node3D

# --- Rotators ---

## godot_basis() and rotator_from_basis() are exact inverses on integer
## rotators, given the original as the reference; without one they still
## return a rotator with the same matrix.
func test_rotators() -> void:
	var cases: Array[Vector3i] = [Vector3i.ZERO, Vector3i(16384, 0, 0), Vector3i(-16384, 0, 0),
		Vector3i(16384, 5000, 1200), Vector3i(-16384, -3000, 700), Vector3i(16383, 12345, -2222),
		Vector3i(-16383, 30000, 32767), Vector3i(16385, -7, 9), Vector3i(-16385, 65535, -65535),
		Vector3i(32768, 100, 200), Vector3i(-32768, 0, 32768), Vector3i(40000, 70000, -100),
		Vector3i(0, 65536, 0), Vector3i(0, -32768, 32768), Vector3i(8192, -8192, 8192),
		Vector3i(49152, 1, 2), Vector3i(100000, -100000, 50000)]
	var rng := RandomNumberGenerator.new()
	rng.seed = 1234
	for i in 3000:
		cases.append(Vector3i(rng.randi_range(-100000, 100000), rng.randi_range(-100000, 100000),
			rng.randi_range(-100000, 100000)))
	for pitch in [16384, -16384, 16383, -16383, 16385, -16385, 49152, -49152, 16384 + 65536]:
		for i in 100:
			cases.append(Vector3i(pitch, rng.randi_range(-70000, 70000), rng.randi_range(-70000, 70000)))

	var exact := 0
	var same_matrix := 0
	var canonical := 0
	var bad: Array[String] = []
	for rot in cases:
		var b := Edits.godot_basis(rot)
		var back := Edits.rotator_from_basis(b, rot)
		if back == rot:
			exact += 1
		elif bad.size() < 5:
			bad.append('%s -> %s' % [rot, back])

		# No reference: another rotator, but the same matrix (rounded to whole units).
		var any := Edits.rotator_from_basis(b)
		if Edits.max_difference(Edits.godot_basis(any), b) <= 2e-4:
			same_matrix += 1
		elif bad.size() < 5:
			bad.append('%s -> %s (no reference)' % [rot, any])

		# A rotator in UE2's own range comes back unchanged even without a reference.
		var p := posmod(rot.x + 32768, 65536) - 32768
		if absi(p) < 16384:
			var c := Vector3i(p, posmod(rot.y + 32768, 65536) - 32768, posmod(rot.z + 32768, 65536) - 32768)
			if Edits.rotator_from_basis(Edits.godot_basis(c)) == c:
				canonical += 1
			elif bad.size() < 5:
				bad.append('%s (canonical) -> %s' % [c, Edits.rotator_from_basis(Edits.godot_basis(c))])
		else:
			canonical += 1

	check(exact == cases.size(), 'rotator round trip exact for %d of %d rotators (pitch +-90 included)' % [
		exact, cases.size()])
	check(same_matrix == cases.size(), 'without a reference, %d of %d decompose to the same matrix' % [
		same_matrix, cases.size()])
	check(canonical == cases.size(), 'canonical rotators come back unchanged without a reference')
	if not bad.is_empty():
		print('        ' + '; '.join(bad))

	# The 90 degree turn about Godot's up axis is a yaw of -16384 in Unreal.
	var turned := Basis(Vector3.UP, PI / 2.0) * Edits.godot_basis(Vector3i(0, 1000, 0))
	check(Edits.rotator_from_basis(turned, Vector3i(0, 1000, 0)) == Vector3i(0, -15384, 0),
		'turning left in Godot is a negative yaw in Unreal')

# --- The Untouched Level ---

## The exported transforms match godot_basis() (Python and GDScript agree),
## and the untouched level has no edits and no warnings.
func test_untouched(packed: PackedScene) -> void:
	var root := packed.instantiate()
	var nodes: Dictionary = Edits.actor_nodes(root)['actors']
	check(nodes.size() == int(root.get_meta('t3_actor_count', -1)), 'finds all %d actors' % nodes.size())

	var worst := 0.0
	var worst_name := ''
	for key in nodes:
		var n: Node3D = nodes[key]
		var o := Edits.origin(n)
		var d := Edits.max_difference(Edits.level_transform(n, root).basis,
			Edits.godot_basis(o['rotation'], o['draw_scale']))
		if d > worst:
			worst = d
			worst_name = key
	check(worst < 1e-6, 'exported bases match godot_basis() (worst %s, %s)' % [String.num_scientific(worst), worst_name])

	var c := Edits.collect(root)
	var doc: Dictionary = c['doc']
	check((doc['actors'] as Dictionary).is_empty(), 'an untouched level has no edits (%d)' % (doc['actors'] as Dictionary).size())
	check((c['warnings'] as Array).is_empty(), 'and no warnings %s' % [c['warnings']])
	check(doc.keys() == ['format', 'version', 'level', 'source', 'actors'], 'document keys %s' % [doc.keys()])
	check(doc['source'] is Dictionary and (doc['source'] as Dictionary).keys() == ['file', 'size', 'sha1'] and
		doc['source']['size'] is int, 'source %s' % [doc['source']])
	root.free()

# --- Edits ---

## Edits the level the way the dock and the gizmos do, saves it, and checks
## the file.  Returns the saved document, or {} on failure.
func test_edits(packed: PackedScene) -> Dictionary:
	var root := packed.instantiate()
	var upm := Edits.units_per_meter(root)

	# Moved one metre along Godot X (Unreal X), gamesys values of every scalar type.
	var crate := actor(root, 'StaticMeshActor0')
	crate.position += Vector3(1, 0, 0)
	crate.set_meta(Edits.EDITS_META, {'Brightness': 2.5, 'Health': 7, 'bActive': false, 'Mode': 3, 'Channel': 9,
		'Target': 'Door2', 'Message': 'say "hi"'})

	# Edits equal to the exported values are no change (1 is true, 7 has no enum name).
	actor(root, 'PlayerStart0').set_meta(Edits.EDITS_META, {'TeleportDestName': 'start'})
	actor(root, 'D_100_0').set_meta(Edits.EDITS_META, {'bLightOn': true, 'Mode': 7})
	var near := actor(root, 'Near_Gimbal')
	near.transform = near.transform

	# Rotations: a turn about the up axis, at pitch +90 and -90, and outside UE2's range.
	var yawed := actor(root, 'Yawed')
	yawed.basis = Basis(Vector3.UP, PI / 2.0) * yawed.basis
	var up := actor(root, 'Gimbal_Up')
	up.basis = Basis(Vector3.UP, PI / 2.0) * up.basis
	actor(root, 'Gimbal_Down').basis = Edits.godot_basis(Vector3i(-16384, -3000, 900))
	actor(root, 'Wound').basis = Edits.godot_basis(Vector3i(40000, 70100, -100))

	# Scale: doubled (uniform), and non-uniform (not saved, with a warning).
	var scaled := actor(root, 'Scaled')
	scaled.scale = scaled.scale * 2.0
	actor(root, 'StaticMeshActor1').scale = Vector3(1, 2, 1)

	# A light raised half a metre.
	var light := actor(root, 'Light0')
	light.position.y += 0.5

	var c := Edits.collect(root)
	var warnings: Array = c['warnings']
	check(warnings.size() == 1 and String(warnings[0]).begins_with('StaticMeshActor1: non-uniform scale'),
		'non-uniform scale is refused with a warning %s' % [warnings])

	var result := Edits.save(root)
	check(result['ok'] and result['path'] == 'res://T3EditTest/T3EditTest.edits.json',
		'saved %d actors to %s %s' % [result['actors'], result['path'], result['error']])
	var text := FileAccess.get_file_as_string(result['path'])
	var got = JSON.parse_string(text)
	if not check(got is Dictionary, 'the edits file is JSON'):
		root.free()
		return {}

	var src := Edits.source(root)
	var expected := {
		'format': 't3-map-edits', 'version': 2, 'level': 'T3EditTest',
		'source': {'file': 'T3EditTest.gmp', 'size': src['size'], 'sha1': src['sha1']},
		'actors': {
			'Gimbal_Down': {'rotation': [-16384, -3000, 900]},
			'Gimbal_Up': {'rotation': [16384, 5000, 17584]},
			'Light0': {'location': [256.0, 256.0, roundf((192.0 + 0.5 * upm) * 100.0) / 100.0]},
			'Scaled': {'draw_scale': 5.0},
			'StaticMeshActor0': {'location': [152.99, -250.25, 32.0], 'gamesys': {'Brightness': 2.5, 'Health': 7,
				'bActive': false, 'Mode': 'MODE_D', 'Channel': 9, 'Target': 'Door2', 'Message': 'say "hi"'}},
			'Wound': {'rotation': [40000, 70100, -100]},
			'Yawed': {'rotation': [0, -15384, 0]},
		},
	}
	var exact := Edits.same_json(got, expected)
	check(exact, 'the file holds exactly the changed values')
	if not exact:
		print('        got      ' + JSON.stringify(got))
		print('        expected ' + JSON.stringify(expected))
	check(text.begins_with('{\n  "format": "t3-map-edits",\n  "version": 2,'), 'format and version come first')
	check(text.contains('"rotation": [0, -15384, 0]') and text.contains('"draw_scale": 5.0'),
		'rotations are written as integers, scales as floats')
	for key in UNTOUCHED:
		if (got['actors'] as Dictionary).has(key):
			check(false, '%s is not in the file' % key)

	# Revert one actor: back to its exported state, and out of the edits.
	Edits.apply_changes([Edits.revert_change(yawed, root)])
	var after: Dictionary = Edits.collect(root)['doc']['actors']
	check(not after.has('Yawed') and after.size() == 6, 'revert removes one actor from the edits')

	# A copy of Yawed moved a metre is a new actor, and a deleted PlayerStart0 a
	# removed one; a node that is no T3 actor is not saved, and deleting the
	# LevelInfo is refused.
	var copy := yawed.duplicate() as Node3D
	yawed.get_parent().add_child(copy)
	copy.position += Vector3(0, 0, 1)
	var extra := Marker3D.new()
	extra.name = 'NewMarker'
	yawed.get_parent().add_child(extra)
	for key in ['PlayerStart0', 'LevelInfo0']:
		var gone := actor(root, key)
		gone.get_parent().remove_child(gone)
		gone.free()

	var with_copy := Edits.collect(root)
	var o := Edits.origin(yawed)
	var loc: PackedFloat64Array = o['location']
	var rot: Vector3i = o['rotation']
	var y := roundf((loc[1] + upm) * 100.0) / 100.0
	var new_actor := {'copy_of': 'Yawed', 'location': [loc[0], y, loc[2]], 'rotation': [rot.x, rot.y, rot.z]}
	check(Edits.same_json(with_copy['doc'].get('added'), [new_actor]),
		'a copy is saved as a new actor %s' % JSON.stringify(with_copy['doc'].get('added')))
	check(Edits.same_json(with_copy['doc'].get('removed'), ['PlayerStart0']), 'a deleted actor is saved as removed')
	check(Edits.same_json(with_copy['doc'].get('not_saved'), {'nodes': 1}), 'a node that is no T3 actor is counted, not saved')
	var w := '\n'.join(with_copy['warnings'])
	check(w.contains('1 node without T3 metadata (NewMarker)') and w.contains('LevelInfo0: the level needs its LevelInfo'),
		'the unsaved node and the kept LevelInfo are reported')
	check(actor(root, 'Yawed') == yawed, 'the original stays the actor, the duplicate is the copy')

	root.free()
	return got

# --- Load ---

## Loading the saved file into a fresh copy of the level reproduces it.
func test_load(packed: PackedScene, saved: Dictionary) -> void:
	var root := packed.instantiate()
	var r := Edits.read(Edits.edits_path(root))
	check(r['error'] == '', 'reads the edits file back %s' % r['error'])
	var plan := Edits.plan_load(root, r['doc'])
	check((plan['warnings'] as Array).is_empty() and (plan['changes'] as Array).size() == 7,
		'plans %d changes %s' % [(plan['changes'] as Array).size(), plan['warnings']])
	Edits.apply_changes(plan['changes'])
	var doc: Dictionary = Edits.collect(root)['doc']
	var again = JSON.parse_string(Edits.to_json(doc))
	var same := Edits.same_json(again, saved)
	check(same, 'the loaded level collects the same edits')
	if not same:
		print('        got      ' + JSON.stringify(again))
	root.free()

## New and removed actors load back: plan_load() makes the copy and deletes
## the removed actor, and the level then collects the same new and removed actors.
func test_load_added(packed: PackedScene) -> void:
	var root := packed.instantiate()
	var yawed := actor(root, 'Yawed')
	var o := Edits.origin(yawed)
	var loc: PackedFloat64Array = o['location']
	var doc := {'format': 't3-map-edits', 'version': 2, 'level': 'T3EditTest', 'actors': {},
		'added': [{'copy_of': 'Yawed', 'location': [loc[0] + 64.0, loc[1], loc[2]], 'rotation': [0, 8192, 0]}],
		'removed': ['PlayerStart0']}
	var plan := Edits.plan_load(root, doc)
	check((plan['warnings'] as Array).is_empty() and (plan['changes'] as Array).size() == 2,
		'plans a new and a removed actor %s' % [plan['warnings']])
	Edits.apply_changes(plan['changes'])
	check(actor(root, 'PlayerStart0') == null, 'the removed actor is deleted')
	var c: Dictionary = Edits.collect(root)['doc']
	check(Edits.same_json(c.get('added'), doc['added']) and Edits.same_json(c.get('removed'), doc['removed']),
		'the level collects the same new and removed actors: %s %s' % [JSON.stringify(c.get('added')),
		JSON.stringify(c.get('removed'))])
	root.free()

# --- Speed ---

## collect() on a level of 5000 actors, the size of a large T3 map.
func test_speed() -> void:
	var root := Node3D.new()
	root.set_meta('t3_level', 'Big')
	var markers := Node3D.new()
	markers.name = 'Markers'
	root.add_child(markers)
	var upm := Edits.DEFAULT_UNITS_PER_METER
	for i in 5000:
		var m := Marker3D.new()
		var o := {'location': [i * 3.5, -i * 1.25, 100.0], 'rotation': [i % 300, i * 7, 0], 'draw_scale': 1.0}
		m.set_meta('t3_name', 'Point%d' % i)
		m.set_meta('t3_origin', JSON.stringify(o))
		m.transform = Edits.placement_transform(Edits.origin(m), upm)
		markers.add_child(m)
	root.set_meta('t3_actor_count', 5000)

	var t0 := Time.get_ticks_msec()
	var c := Edits.collect(root)
	var ms := Time.get_ticks_msec() - t0
	print('  time  collect() on 5000 actors: %d ms' % ms)
	check((c['doc']['actors'] as Dictionary).is_empty(), 'a large untouched level has no edits')
	root.free()

# --- Older Exports ---

## A scene exported before the plugin existed (no t3_origin) gets one warning
## and no edits, rather than a warning per actor.
func test_old_export(packed: PackedScene) -> void:
	var root := packed.instantiate()
	for n in Edits.actor_nodes(root)['actors'].values():
		n.remove_meta('t3_origin')
	var c := Edits.collect(root)
	var w: Array = c['warnings']
	check(w.size() == 1 and String(w[0]).begins_with('13 actors without t3_origin metadata')
		and (c['doc']['actors'] as Dictionary).is_empty(), 'an older export gets one warning and no edits %s' % [w])
	check(not Edits.is_outdated(root) and Edits.export_version(root) == Edits.EXPORT_VERSION,
		'the exporter stamps the export format this plugin is made for (%d)' % Edits.export_version(root))

	# Unstamped: exported before scenes carried an export format.
	root.remove_meta('t3_export_version')
	w = Edits.collect(root)['warnings']
	check(Edits.is_outdated(root) and String(w[0]).begins_with('exported by older tools (export format 0'),
		'a scene from older tools is reported first %s' % [w.slice(0, 1)])
	root.free()

# --- Saved Edits In An Export ---

## The level exported with saved edits (the scene at `path`) holds them
## already: loading its edits file again makes no new actor and deletes none,
## and the level then collects the same edits as before.
func test_saved_export(path: String) -> void:
	var packed := load(path) as PackedScene
	if not check(packed != null, 'loads %s' % path):
		return

	var root := packed.instantiate()
	var r := Edits.read(Edits.edits_path(root))
	check(r['error'] == '', 'reads its edits file %s' % r['error'])
	var before := Edits.to_json(Edits.collect(root)['doc'])
	var plan := Edits.plan_load(root, r['doc'])
	var made := (plan['changes'] as Array).filter(func(c): return c.has('create') or c.has('delete'))
	check(made.is_empty() and (plan['warnings'] as Array).is_empty(),
		'loading the saved edits into the export again makes and deletes no actor %s' % [plan['warnings']])

	Edits.apply_changes(plan['changes'])
	var after := Edits.to_json(Edits.collect(root)['doc'])
	check(after == before, 'and the level collects the same edits')
	root.free()
