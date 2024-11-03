class_name FoodItem extends StaticBody2D

@onready var sprite_2d: Sprite2D = $Sprite2D
@onready var animator: AnimationPlayer = $Animator


func eaten():
	animator.play("fade_away")
