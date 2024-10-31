class_name PlayerState extends Node

signal finished(next_state: String, data: Dictionary)

var player: Player
var sm: StateMachine

func enter(_data := {}) -> void:
	player.animator.play(self.name)

func exit() -> void:
	pass

func handle_input(_event: InputEvent) -> void:
	pass

func update(_delta: float) -> void:
	pass

func physics_update(_delta: float) -> void:
	pass
