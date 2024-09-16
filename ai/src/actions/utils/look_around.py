from src.goap.worldstate import WorldState
from src.player.player import Player
from src.utils.logger import Logger


def look_around(world_state: WorldState) -> None:
    try:
        player: Player = world_state.get("player")
        player.look_around()
    except Exception as e:
        Logger.log(ID="error", message=f"An error happened while trying to look around: {e}")
