from src.goap.worldstate import WorldState
from src.player.player import Player
from src.utils.logger import Logger


def move(world_state: WorldState) -> None:
    try:
        player: Player = world_state.get("player")
        player.move()
    except Exception as e:
        Logger.log(ID="error", message=f"An error happened while trying to move: {e}")
