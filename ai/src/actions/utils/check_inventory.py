from src.goap.worldstate import WorldState
from src.player.player import Player
from src.utils.logger import Logger


def check_inventory(world_state: WorldState) -> None:
    try:
        player: Player = world_state.get("player")
        player.check_inventory()
    except Exception as e:
        Logger.log(ID="error", message=f"An error happened while trying to check the inventory: {e}")
