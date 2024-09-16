from copy import deepcopy
from typing import List
from src.data.tile import Tile
from src.goap.worldstate import WorldState


def create_temp_world_state(world_state: WorldState) -> WorldState:
    tiles: List[Tile] = world_state.get("tiles")

    temp_world_state = WorldState()
    temp_world_state.state = world_state.state.copy()
    temp_world_state.set("tiles", deepcopy(tiles))
    temp_world_state.set("know_tiles", bool(tiles))
    temp_world_state.set("player_food", world_state.get("player").inventory.food)

    return temp_world_state
