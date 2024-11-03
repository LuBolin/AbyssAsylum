class_name BossUtils extends Node2D
@export var max_health := 3
var health: int = max_health

var player: Player

func _ready() -> void:
	# self -> boss -> boss room
	var room = get_parent().get_parent()
	for child in room.get_children():
		if child is Player:
			player = child
			break
	assert(player != null)

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
