from src.goap.worldstate import WorldState
from src.data.stone_type import StoneType
from src.data.tile import Tile
from src.player.player import Player
from typing import List, Optional


def harvest_stone(
        world_state: WorldState,
        stone_type: StoneType,
        player: Player,
        tile: Tile,
        final: bool
):
    stone_count = tile.inventory.stones.get_amount(stone_type)
    if stone_count >= 1:
        tile.inventory.stones.decrease_amount_by(stone_type)

        if final:
            player.take_object(str(stone_type))
            world_state.get("tiles")[0].inventory.stones.decrease_amount_by(stone_type)


def harvest_food(
        world_state: WorldState,
        player: Player,
        tile: Tile,
        final: bool
):
    food_count = tile.inventory.food
    if food_count >= 1:
        for _ in range(food_count):
            world_state.set("player_food", world_state.get("player_food") + 1)
            tile.inventory.food -= 1

        if final:
            for _ in range(food_count):
                player.take_object("food")
                world_state.get("tiles")[0].inventory.food -= 1


def harvest_resource(world_state: WorldState, resource_type: str, final: bool = False):
    tiles: Optional[List[Tile]] = world_state.get("tiles")
    player: Optional[Player] = world_state.get("player")
    if player is not None and tiles is not None and len(tiles) != 0:
        if StoneType.is_stone(resource_type):
            harvest_stone(
                world_state,
                StoneType.from_str(resource_type),
                player,
                tiles[0],
                final
            )
        elif resource_type == "food":
            harvest_food(
                world_state,
                player,
                tiles[0],
                final
            )
