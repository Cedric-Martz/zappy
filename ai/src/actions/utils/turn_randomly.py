from src.goap.worldstate import WorldState
from src.player.player import Player


def turn_randomly(world_state: WorldState):
    import random

    player: Player = world_state.get("player")
    directions = ["left", "right"]

    if player.world_state.get("turn_direction") == "none":
        player.world_state.set("turn_direction", random.choice(directions))

    if player.world_state.get("turn_direction") == "left":
        player.turn_left()
    elif player.world_state.get("turn_direction") == "right":
        player.turn_right()

    player.world_state.set("turn_count", player.world_state.get("turn_count") + 1)
    if player.world_state.get("turn_count") > 3:
        player.world_state.set("turn_count", 0)
        player.world_state.set("turn_direction", "none")
        player.move()
