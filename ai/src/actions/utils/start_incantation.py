from src.goap.worldstate import WorldState
from src.player.player import Player
from src.data.values_by_level import values_by_level
from src.utils.logger import Logger


def start_incantation(world_state: WorldState):
    try:
        player: Player = world_state.get("player")
        for (stone, quantity) in values_by_level[player.world_state.get("level")].stones.stones.items():
            stone_name = str(stone)
            for _ in range(quantity):
                player.set_object_down(stone_name)
        player.start_incantation()
    except Exception as e:
        Logger.log(ID="error", message=f"An error happened while trying to start the incantation: {e}")
