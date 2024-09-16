from src.goap.worldstate import WorldState
from src.data.stone_type import StoneType
from src.data.tile import Tile
from typing import List
from src.data.inventory import Inventory


def check_stone(
        stone_type: StoneType,
        tile: Tile,
        limit: int = 1
) -> bool:
    stone_count = tile.inventory.stones.get_amount(stone_type)
    return stone_count >= limit


def check_food(
        tile: Tile,
        limit: int = 1
) -> bool:
    food_count = tile.inventory.food
    return food_count >= limit


def check_resources_on_tile(tile: Tile, inventory: Inventory) -> bool:
    if check_food(tile, inventory.food):
        return True
    return inventory.stones.compare(tile.inventory.stones).check_validity()


def check_resource(world_state: WorldState, resource_type: str) -> bool:
    temptiles = world_state.get("tiles")
    if temptiles is not None:
        tiles: List[Tile] = temptiles
        if len(tiles) != 0:
            if StoneType.is_stone(resource_type):
                return check_stone(
                    StoneType.from_str(resource_type),
                    tiles[0]
                )
            if resource_type == "food":
                return check_food(
                    tiles[0]
                )
    return False
