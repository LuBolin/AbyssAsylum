class_name EatingDisorderBoss extends CharacterBody2D

@onready var boss_utils: BossUtils = $BossUtils
@onready var animator: AnimatedSprite2D = $Animator
@onready var acid_scene: PackedScene = \
	preload("res://bosses/eating_disorder/phase_2/acid_proj.tscn")

signal hit_wall

enum States {
	WALK,
	CHARGE,
	EATING,
	DEAD
}

var player: Player
var current_state: States = States.WALK

# movement variables
var speed: float = 50
var charging_speed: float = 150
var turning_rate: float = 30
var stun_durn: float = 0.5

var facing_right: bool = true
var walk_to_charge_breakpoint: float = 3.0
var walk_timer: float = 0.0
var charge_dirn: Vector2 = Vector2.ZERO
var second_phase: bool = true

func _ready() -> void:
	await boss_utils.player.ready
	player = boss_utils.player

func _process(delta: float) -> void:
	# self.look_at(player.global_position)
	# should face left
	if (self.global_position.x > player.global_position.x):
		if (not animator.flip_h):
			animator.flip_h = true
	else: # should face right
		if (animator.flip_h):
			animator.flip_h = false


func _physics_process(delta: float) -> void:
	var dirn = player.global_position - self.global_position
	dirn = dirn.normalized()
	
	if current_state == States.WALK:
		var kc2d: KinematicCollision2D = \
			move_and_collide(dirn * speed * delta)
		if kc2d != null:
			var object_hit: Object = kc2d.get_collider()
			if object_hit is Player:
				print("Player hit")
		
		walk_timer += delta
		if (walk_timer >= walk_to_charge_breakpoint):
			_acid_attack()
			current_state = States.CHARGE
			# initialize charge dirn
			charge_dirn = dirn
	
	if current_state == States.CHARGE:
		# we have prev_charge dirn
		# as well as dirn to player
		# rotate prev_charge as nessessary
		# up to a certain limit
		
		var delta_theta: float = charge_dirn.angle_to(dirn)
		delta_theta = rad_to_deg(delta_theta)
		var turn_limit = turning_rate * delta
		delta_theta = clampf(delta_theta, -turn_limit ,turn_limit)
		delta_theta = deg_to_rad(delta_theta)
		charge_dirn = charge_dirn.rotated(delta_theta)
		
		var kc2d: KinematicCollision2D = \
			move_and_collide(charge_dirn * charging_speed * delta)
		if kc2d != null:
			var object_hit: Object = kc2d.get_collider()
			if object_hit is Player:
				print("Player hit")
			elif object_hit is TileMapLayer:
				# print("Burger time")
				hit_wall.emit()
				charge_dirn = dirn
				current_state = States.WALK
			elif object_hit is FoodItem:
				object_hit.eaten()
				current_state = States.EATING

func _acid_attack() -> void:
	var acid_item: Node2D = acid_scene.instantiate()
	self.get_parent().add_child(acid_item)
	acid_item.global_position.x = self.global_position.x
	acid_item.global_position.y = self.global_position.y
	acid_item.activate()
