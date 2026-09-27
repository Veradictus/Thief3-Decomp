extends SceneTree

## Renders an exported scene to a PNG for visual checks (needs a window/GPU,
## so run it without --headless).
##
## Usage:
##   godot --path <project> --script res://t3_tools/render_scene.gd -- <scene> <out.png>
##         [camera_x camera_y camera_z target_x target_y target_z] [--fov 70] [--ambient 0.6]
##
## Without a camera position the camera looks at the scene's AABB centre from
## above and to the side.  The level's own WorldEnvironment (dark ambient and
## fog from LevelInfo) is replaced by a bright preview environment.

# =============================================================================
# VARIABLES
# =============================================================================

## Output PNG path, from the command line.
var _out := ''

## Frames rendered so far; the shot is saved a few frames in so the scene has
## settled first.
var _frames := 0

# =============================================================================
# METHODS
# =============================================================================

## Parses the command line, replaces the level's own environment with a bright
## preview one, places the camera, and waits for a few frames to render before
## handle_frame_post_draw() saves the screenshot.
func _init() -> void:
	var args := OS.get_cmdline_user_args()
	if args.size() < 2:
		push_error('usage: -- <scene> <out.png> [cx cy cz tx ty tz] [--fov F] [--ambient A]')
		quit(2)
		return

	var fov := 70.0
	var ambient := 0.6
	var nums: Array[float] = []
	var i := 2
	while i < args.size():
		if args[i] == '--fov':
			fov = float(args[i + 1]); i += 2
		elif args[i] == '--ambient':
			ambient = float(args[i + 1]); i += 2
		else:
			nums.append(float(args[i])); i += 1

	_out = args[1]
	var packed := load(args[0]) as PackedScene
	if packed == null:
		push_error('cannot load ' + args[0])
		quit(1)
		return

	var scene := packed.instantiate()

	# Replace the level's own (dark, fogged) environment with a bright preview one.
	for n in scene.find_children('*', 'WorldEnvironment', true, false):
		n.get_parent().remove_child(n)
		n.free()
	root.add_child(scene)

	var env := Environment.new()
	env.background_mode = Environment.BG_COLOR
	env.background_color = Color(0.08, 0.09, 0.12)
	env.ambient_light_source = Environment.AMBIENT_SOURCE_COLOR
	env.ambient_light_color = Color(1, 1, 1)
	env.ambient_light_energy = ambient
	var we := WorldEnvironment.new()
	we.environment = env
	root.add_child(we)

	var cam := Camera3D.new()
	cam.fov = fov
	cam.far = 4000.0
	root.add_child(cam)

	# An explicit camera position and target were given on the command line.
	if nums.size() >= 6:
		cam.transform = Transform3D(Basis(), Vector3(nums[0], nums[1], nums[2])).looking_at(
			Vector3(nums[3], nums[4], nums[5]), Vector3.UP)
	else:
		var box := scene_aabb(scene)
		var c := box.get_center()
		var r := box.size.length() * 0.6
		cam.transform = Transform3D(Basis(), c + Vector3(r * 0.6, r * 0.7, r * 0.6)).looking_at(c, Vector3.UP)

	cam.current = true
	RenderingServer.frame_post_draw.connect(handle_frame_post_draw)

## Saves the frame once the scene has had a few frames to settle, then quits.
func handle_frame_post_draw() -> void:
	_frames += 1
	if _frames != 5:
		return

	var img := root.get_viewport().get_texture().get_image()
	img.save_png(_out)
	print('saved ', _out, ' ', img.get_size())
	quit(0)

## Combined AABB of every GeometryInstance3D under `n`, in world space.
func scene_aabb(n: Node) -> AABB:
	var box := AABB()
	var have := false
	var stack: Array[Node] = [n]

	while not stack.is_empty():
		var x: Node = stack.pop_back()
		for c in x.get_children():
			stack.push_back(c)

		if x is GeometryInstance3D:
			var b := xform(x as Node3D) * (x as VisualInstance3D).get_aabb()
			box = b if not have else box.merge(b)
			have = true

	return box

## `n`'s transform in world space, computed by walking its parents by hand.
func xform(n: Node3D) -> Transform3D:
	var t := n.transform
	var p := n.get_parent()

	while p != null:
		if p is Node3D:
			t = (p as Node3D).transform * t
		p = p.get_parent()

	return t
