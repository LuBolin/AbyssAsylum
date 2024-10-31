class_name BaseBoss extends Node2D
@export var max_health := 3
var health: int = max_health


func hit():
	print(self.name+" was hit")
	print("HP was "+str(health))
	health -= 1
	print("HP is "+str(health))
	if health <= 0:
		get_tree().create_timer(0.3)\
			.timeout.connect(die)

func die():
	queue_free()
