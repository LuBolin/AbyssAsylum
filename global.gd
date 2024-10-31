extends Node

func _ready() -> void:
	add_input_key("move_up", KEY_W)
	add_input_key("move_left", KEY_A)
	add_input_key("move_down", KEY_S)
	add_input_key("move_right", KEY_D)
	add_input_key("roll", KEY_SHIFT)
	add_input_mouse("attack", MOUSE_BUTTON_LEFT)

func add_input_key(input_name: String, input_key: Key):
	InputMap.add_action(input_name)
	var event_space = InputEventKey.new()
	event_space.physical_keycode = input_key
	InputMap.action_add_event(input_name, event_space)

func add_input_mouse(input_name: String, input_mouse: MouseButton):
	InputMap.add_action(input_name)
	var event_space = InputEventMouseButton.new()
	event_space.button_index = input_mouse
	InputMap.action_add_event(input_name, event_space)
