from src.goap.worldstate import WorldState
from src.player.player import Player
from src.utils.logger import Logger


def drop_advanced_elevate_values(world_state: WorldState):
    try:
        player: Player = world_state.get("player")
        player.set_object_down("linemate")

    except Exception as e:
        Logger.log(ID="error", message=f"An error happened while trying to drop objects: {e}")
        return False
