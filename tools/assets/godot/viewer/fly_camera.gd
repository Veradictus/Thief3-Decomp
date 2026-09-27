extends Camera3D

## Free-fly camera.
##
## - Move with the t3_move_* actions (W A S D, Q/E or Ctrl/Space by default).
## - Look while the right mouse button is held, or while the mouse is captured
##   (set_captured, toggled by the viewer).
## - t3_fast / t3_slow (Shift / Alt) multiply the speed; the mouse wheel changes
##   the base speed.  Speeds are in metres per second.
## - Movement is smoothed with an exponential response, so it behaves the same
##   at any frame rate.

# =============================================================================
# VARIABLES
# =============================================================================

## Current base movement speed, in metres per second.
@export var base_speed := 4.0

## Speed multiplier while t3_fast (Shift) is held.
@export var fast_factor := 4.0

## Speed multiplier while t3_slow (Alt) is held.
@export var slow_factor := 0.25

## Lower clamp for change_speed().
@export var min_speed := 0.25

## Upper clamp for change_speed().
@export var max_speed := 400.0

## How quickly the velocity follows the input, in 1/s.
@export var response := 12.0

## Mouse look sensitivity, in degrees per pixel.
@export var mouse_sensitivity := 0.12

## Current yaw (heading), in radians.
var yaw := 0.0

## Current pitch, in radians.
var pitch := 0.0

## Current smoothed movement velocity, in metres per second.
var velocity := Vector3.ZERO

## Whether the mouse is captured for looking (toggled by the viewer).
var captured := false

## Whether movement and look input are processed at all.
var input_enabled := true

## Whether the right mouse button is currently held (also enables looking).
var _right_held := false

# =============================================================================
# SIGNALS
# =============================================================================

## Emitted when the base speed changes (mouse wheel), so the HUD can show it.
signal speed_changed(base_speed: float)

# =============================================================================
# METHODS
# =============================================================================

## Applies the initial (zero) rotation.
func _ready() -> void:
	apply_rotation()

## Places the camera at `pos` looking at `target` (both in metres).
func look_from(pos: Vector3, target: Vector3) -> void:
	position = pos
	var d := target - pos

	# target == pos: look forward rather than computing an undefined direction.
	if d.length_squared() < 1e-8:
		d = Vector3.FORWARD
	d = d.normalized()

	yaw = atan2(-d.x, -d.z)
	pitch = asin(clampf(d.y, -1.0, 1.0))
	velocity = Vector3.ZERO
	apply_rotation()

## Captures or releases the mouse for looking.
func set_captured(on: bool) -> void:
	captured = on
	update_mouse_mode()

## Whether the camera currently responds to mouse look (captured, or the
## right mouse button is held).
func is_looking() -> bool:
	return captured or _right_held

## The current base speed with the fast/slow modifiers applied.
func effective_speed() -> float:
	var s := base_speed
	if Input.is_action_pressed('t3_fast'):
		s *= fast_factor
	if Input.is_action_pressed('t3_slow'):
		s *= slow_factor
	return s

## Multiplies the base speed by `factor`, clamped to [min_speed, max_speed],
## and emits speed_changed.
func change_speed(factor: float) -> void:
	base_speed = clampf(base_speed * factor, min_speed, max_speed)
	speed_changed.emit(base_speed)

## Rebuilds the camera's basis from yaw and pitch.
func apply_rotation() -> void:
	transform.basis = Basis(Vector3.UP, yaw) * Basis(Vector3.RIGHT, pitch)

## Captures or releases the OS mouse cursor to match is_looking().
func update_mouse_mode() -> void:
	var want := Input.MOUSE_MODE_CAPTURED if is_looking() else Input.MOUSE_MODE_VISIBLE
	if Input.mouse_mode != want:
		Input.mouse_mode = want

## Mouse-look toggle/aim and the speed-changing scroll wheel.
func _unhandled_input(event: InputEvent) -> void:
	if not input_enabled:
		return

	if event is InputEventMouseButton:
		var mb := event as InputEventMouseButton
		if mb.is_action('t3_look'):
			_right_held = mb.pressed
			update_mouse_mode()
			get_viewport().set_input_as_handled()
		elif mb.pressed and mb.button_index == MOUSE_BUTTON_WHEEL_UP:
			change_speed(1.2)
			get_viewport().set_input_as_handled()
		elif mb.pressed and mb.button_index == MOUSE_BUTTON_WHEEL_DOWN:
			change_speed(1.0 / 1.2)
			get_viewport().set_input_as_handled()
	elif event is InputEventMouseMotion and is_looking():
		var mm := event as InputEventMouseMotion
		yaw -= deg_to_rad(mm.relative.x * mouse_sensitivity)
		pitch = clampf(pitch - deg_to_rad(mm.relative.y * mouse_sensitivity), deg_to_rad(-89.0), deg_to_rad(89.0))
		apply_rotation()
		get_viewport().set_input_as_handled()

## Releases the held-right-button look state when the window loses focus, so
## a stray drag doesn't get stuck.
func _notification(what: int) -> void:
	if what == NOTIFICATION_APPLICATION_FOCUS_OUT or what == NOTIFICATION_WM_WINDOW_FOCUS_OUT:
		_right_held = false
		update_mouse_mode()

## Smoothly accelerates towards the input-driven target velocity and moves the camera.
func _process(delta: float) -> void:
	var target := Vector3.ZERO
	if input_enabled:
		var right := Input.get_axis('t3_move_left', 't3_move_right')
		var back := Input.get_axis('t3_move_forward', 't3_move_back')
		var up := Input.get_axis('t3_move_down', 't3_move_up')
		var b := transform.basis
		var move := b.x * right + b.z * back + Vector3.UP * up

		# Avoid normalizing a zero vector.
		if move.length_squared() > 1e-6:
			target = move.normalized() * effective_speed()

	velocity = velocity.lerp(target, 1.0 - exp(-response * delta))

	# Snap to a full stop once the exponential decay is negligible.
	if target == Vector3.ZERO and velocity.length_squared() < 1e-6:
		velocity = Vector3.ZERO
	position += velocity * delta
