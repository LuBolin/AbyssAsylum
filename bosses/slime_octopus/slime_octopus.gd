class_name SlimeOctupus extends BaseBoss

@export var target: Node2D
@export var root_motion_offset: float = 0
@export var exposed: bool = false

var total_rm_offset: float = 240
var attacking: bool = false
var direction: Vector2 = Vector2.RIGHT
var attack_origin: Vector2
var been_hit: bool = false

@onready var animator: AnimationPlayer = $Animator
@onready var sprite: Sprite2D = $Sprite

var damage = 1

func _ready() -> void:
	animator.animation_finished.connect(_anim_cleanup)

func _unhandled_input(_event: InputEvent) -> void:
	# debug test
	if Input.is_action_just_pressed("ui_down"):
		attack_1()

func attack_1():
	attacking = true
	attack_origin = self.global_position
	animator.play("attack_1")

func _process(_delta: float) -> void:
	var should_flip = direction.x < 0
	var is_flipped = self.scale.x == -1
	if should_flip != is_flipped:
		self.scale.x *= -1
	# print(exposed)

func _physics_process(_delta: float) -> void:
	if attacking:
		self.global_position = attack_origin + direction * root_motion_offset
	else:
		if target:
			var offset = target.position - self.position
			direction = offset.normalized()
			look_at(target.position)
			if offset.length() < 200:
				attack_1()
			else:
				translate(direction)

func _anim_cleanup(_anim_name: String):
	attacking = false
	self.global_position = attack_origin + direction * total_rm_offset
	root_motion_offset = 0
	been_hit = false

func hit():
	if not exposed:
		return
	if been_hit:
		return
	exposed = false
	been_hit = true
	super.hit()
