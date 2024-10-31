class_name AttackState extends PlayerState

var weapon: Weapon

func enter(_data := {}) -> void:
	# in practice, maybe freeze the player?
	player.animator.play("Idle")
	weapon = player.weapon.get_child(0)
	weapon.animator.play('attack')
	await weapon.animator.animation_finished
	exit_attack()

func exit() -> void:
	pass

func handle_input(_event: InputEvent) -> void:
	pass

func update(_delta: float) -> void:
	pass

func physics_update(_delta: float) -> void:
	pass

func exit_attack():
	if Input.is_action_just_pressed("roll"):
		finished.emit("Roll")
		return
	
	if player.get_input_dirn().length() > 0:
		finished.emit("Run")
		return
	
	finished.emit("Idle")
