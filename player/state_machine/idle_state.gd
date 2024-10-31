class_name IdleState extends PlayerState

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
	
	if player.get_input_dirn().length() > 0:
		finished.emit("Run")
		return

func update(_delta: float) -> void:
	var should_flip_h = player.get_aim_delta().x < 0
	var is_flipped = player.flip_wrapper.scale.x == -1
	if should_flip_h != is_flipped:
		player.flip_wrapper.scale.x *= -1

func physics_update(_delta: float) -> void:
	pass
