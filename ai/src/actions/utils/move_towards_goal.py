from src.goap.worldstate import WorldState
from src.player.player import Player
from src.utils.logger import Logger


def move_towards_goal(world_state: WorldState) -> None:
    try:
        player: Player = world_state.get("player")
        goal_direction = player.world_state.get("gather_direction")

        if goal_direction in [2, 3, 4]:
            player.turn_left()
        elif goal_direction == 5:
            player.turn_left()
            player.turn_left()
        elif goal_direction in [6, 7, 8]:
            player.turn_right()

        player.move()

    except Exception as e:
        Logger.log(ID="error", message=f"An error happened while trying to move towards goal: {e}")
