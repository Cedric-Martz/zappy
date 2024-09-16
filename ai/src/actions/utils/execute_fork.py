from src.goap.worldstate import WorldState
from src.player.player import Player
from src.utils.logger import Logger


def execute_fork(world_state: WorldState):
    try:
        player: Player = world_state.get("player")
        player.fork()

    except Exception as e:
        Logger.log(ID="error", message=f"An error happened while trying to fork: {e}")
        return False
