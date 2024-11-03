class_name Player extends CharacterBody2D

signal hit(source, damage)
#signal died

@export var speed := 200
@export var roll_speed := 400
@export var roll_cooldown := 1.5

var last_dirn: Vector2 = Vector2.RIGHT
var roll_cd_left: float = 0

@onready var flip_wrapper: Node2D = $FlipWrapper
@onready var animator: AnimatedSprite2D = %Animator
@onready var weapon: Node2D = %Weapon

func _ready() -> void:
	hit.connect(_on_hit)

func _on_hit(_source, _damage):
	# if dmg > 0: transition to hit state
	# print("Hit by " + str(source) + " for " + str(damage))
	pass

func get_aim() -> Vector2:
	return get_global_mouse_position()

func get_aim_delta() -> Vector2:
	var mouse_pos = get_aim()
	return mouse_pos - self.global_position

func get_input_dirn() -> Vector2:
	var input_vector: Vector2 = Vector2(
		Input.get_axis("move_left", "move_right"),
		Input.get_axis("move_up", "move_down")
	)
	# clamp to a magnitude of 1
	if input_vector.length() > 1:
		input_vector /= input_vector.length()
	return input_vector

func _physics_process(delta: float) -> void:
	if velocity.length() > 0:
		last_dirn = velocity.normalized()
	
	if roll_cd_left > 0:
		roll_cd_left -= delta


func _on_hurt_box_body_entered(body: Node2D) -> void:
	if 'damage' in body:
		var dmg = body.get('damage')
		hit.emit(body, dmg)
