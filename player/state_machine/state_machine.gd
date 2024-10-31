class_name StateMachine extends Node


@export var initial_state: PlayerState = null

var player: Player
var states: Dictionary = {'a': 1,}

@onready var curr_state: PlayerState \
	= initial_state if initial_state != null else get_child(0)


func _ready() -> void:
	player = get_parent()
	assert (player is Player)
	
	for state_node in get_children():
		if not state_node is PlayerState:
			continue
		state_node.finished.connect(_state_transition)
		state_node.player = player
		state_node.sm = self
		states[state_node.name] = state_node
	
	await owner.ready
	curr_state.enter()

func _unhandled_input(event: InputEvent) -> void:
	curr_state.handle_input(event)

func _process(delta: float) -> void:
	curr_state.update(delta)

func _physics_process(delta: float) -> void:
	curr_state.physics_update(delta)


func _state_transition(next_state: String, data: Dictionary = {}):
	if next_state not in states:
		push_error("Non-existent state "+next_state)
	if states[next_state] is RollState:
		if player.roll_cd_left <= 0:
			player.roll_cd_left = player.roll_cooldown
		else:
			return
	curr_state.exit()
	curr_state = states[next_state]
	curr_state.enter(data)
