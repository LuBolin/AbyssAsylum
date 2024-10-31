class_name RollState extends PlayerState

func enter(data := {}) -> void:
	super.enter(data)
	player.weapon.hide()
	await player.animator.animation_finished
	exit_roll()

func exit() -> void:
	player.weapon.show()
	pass

func handle_input(_event: InputEvent) -> void:
	pass

func update(_delta: float) -> void:
	pass

func physics_update(_delta: float) -> void:
	var dirn = player.last_dirn
	
	player.velocity = dirn * player.roll_speed
	player.move_and_slide()

func exit_roll():
	if player.get_input_dirn().length() > 0:
		finished.emit("Run")
		return
	else:
		finished.emit("Idle")
