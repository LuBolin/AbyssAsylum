extends Node2D

@onready var boss: EatingDisorderBoss = $EatingDisorder
@onready var top_left: Node2D = $top_left
@onready var btm_right: Node2D = $btm_right

@onready var food_scene: PackedScene = \
	preload("res://bosses/eating_disorder/food_item.tscn")

var min_x: float
var max_x: float
var min_y: float
var max_y: float

var rng: RandomNumberGenerator = RandomNumberGenerator.new()

func _ready() -> void:
	boss.hit_wall.connect(generate_food)
	min_x = top_left.global_position.x
	min_y = top_left.global_position.y
	max_x = btm_right.global_position.x
	max_y = btm_right.global_position.y

func generate_food():
	var randx = rng.randf_range(min_x, max_x)
	var randy = rng.randf_range(min_y, max_y)
	var food_item: Node2D = food_scene.instantiate()
	self.add_child(food_item)
	food_item.global_position.x = randx
	food_item.global_position.y = randy
