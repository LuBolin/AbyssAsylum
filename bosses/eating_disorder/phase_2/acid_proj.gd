class_name AcidProj extends CharacterBody2D

@onready var sprite_2d: Sprite2D = $Sprite2D
# @onready var animator: AnimationPlayer = $Animator 
@onready var puddle_scene: PackedScene = \
	preload("res://bosses/eating_disorder/phase_2/acid_puddle.tscn")

var dirn: Vector2 = Vector2.ZERO
var target: Vector2 = Vector2.ZERO
var activated: bool = false

@export var speed := 200

func _physics_process(delta: float) -> void:
	if not activated:
		return
	move_and_collide(dirn * speed * delta)
	if !(target - self.global_position).normalized().is_equal_approx(dirn):
		# burst function is called
		print((target - self.global_position).normalized())
		print(dirn)
		_burst()

func _burst() -> void:
	var puddle_item: Node2D = puddle_scene.instantiate()
	get_tree().root.add_child(puddle_item)
	puddle_item.global_position.x = self.global_position.x
	puddle_item.global_position.y = self.global_position.y
	queue_free()

func activate() -> void:
	activated = true
	target = Vector2(randf_range(-477, 453), randf_range(-222, 217))
	dirn = target - self.global_position
	dirn = dirn.normalized()
	
