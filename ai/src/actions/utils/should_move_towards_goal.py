from src.goap.worldstate import WorldState
from src.player.player import Player
from src.utils.logger import Logger


def should_move_towards_goal(world_state: WorldState) -> bool:
    try:
        player: Player = world_state.get("player")
        return player.world_state.get("should_gather") and not player.world_state.get("at_goal") and player.world_state.get("gather_direction") != -1
    except Exception as e:
        Logger.log(ID="error", message=f"An error happened while trying to check if we should move towards goal: {e}")
    return False
