class_name RunState extends PlayerState

func enter(data := {}) -> void:
	super.enter(data)

func exit() -> void:
	pass

func handle_input(_event: InputEvent) -> void:
	if Input.is_action_just_pressed("attack"):
		finished.emit("Attack")
		return
	
	if Input.is_action_just_pressed("roll"):
		finished.emit("Roll")
		return

func update(_delta: float) -> void:
	var should_flip_h = player.velocity.x < 0
	var is_flipped = player.flip_wrapper.scale.x == -1
	if should_flip_h != is_flipped:
		player.flip_wrapper.scale.x *= -1

func physics_update(_delta: float) -> void:
	var input_vector = player.get_input_dirn()
	
	player.velocity = input_vector.normalized() * player.speed
	player.move_and_slide()
	
	
	if is_equal_approx(input_vector.length(), 0.0):
		finished.emit('Idle')
