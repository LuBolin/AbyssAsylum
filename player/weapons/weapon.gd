class_name Weapon extends Node2D

var animator: AnimationPlayer

func _ready() -> void:
	animator = get_node("Animator")
	assert (animator != null)
