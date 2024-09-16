from src.goap.worldstate import WorldState
from src.utils.logger import Logger
from src.actions.utils.check_resource import check_resources_on_tile
from src.data.inventory import Inventory
from src.data.values_by_level import full_stones_level
from src.data.tile import Tile
from typing import List


def should_move(world_state: WorldState) -> bool:
    try:
        tiles = world_state.get("tiles")
        inventory = Inventory()
        inventory.stones = full_stones_level.stones
        inventory.food = 1

        for tile in tiles:
            if check_resources_on_tile(tile, inventory):
                return True
        return False
    except Exception as e:
        Logger.log(ID="error", message=f"Error in should move: {e}")
        return False


def should_not_move(world_state: WorldState) -> bool:
    try:
        tiles: List[Tile] = world_state.get("tiles")
        inventory = Inventory()
        inventory.stones = full_stones_level.stones
        inventory.food = 1

        for tile in tiles:
            if check_resources_on_tile(tile, inventory):
                return False
        return True
    except Exception as e:
        Logger.log(ID="error", message=f"Error in should not move: {e}")
        return False
