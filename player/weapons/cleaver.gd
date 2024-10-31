class_name Cleaver extends Weapon

@onready var hit_area: Area2D = $Sprite/HitArea

func _ready() -> void:
	super._ready()
	hit_area.body_entered.connect(_on_body_hit)

func _on_body_hit(body: Node2D):
	if body is Player:
		pass
	if body is BaseBoss:
		print("Hit: " + body.name)
		body.hit()
