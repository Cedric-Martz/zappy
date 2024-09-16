from src.data.stone_type import StoneType
from src.data.inventory import Inventory
from src.data.tile import Tile
from src.data.values_by_level import full_stones_level
from src.goap.worldstate import WorldState
from src.player.player import Player
from src.data.stones import Stones
from src.utils.logger import Logger
from math import sqrt
from typing import List, Tuple


def get_needed_stones(player: Player, tile_inventory: Stones) -> dict:
    try:
        needed_stones_diff = (player.inventory.stones.compare_pos(full_stones_level.stones)).compare(tile_inventory)

        needed_stones = {}
        for stone_type in StoneType:
            needed_amount = needed_stones_diff.get_amount(stone_type)
            if needed_amount > 0:
                needed_stones[stone_type] = needed_amount

        return needed_stones

    except Exception as e:
        Logger.log(ID="error", message=f"An error happened while calculating needed stones: {e}")
        return {}


def get_tile_coordinates(tile_index: int) -> Tuple[int, int]:
    level = 0
    while tile_index >= (2 * level + 1):
        tile_index -= (2 * level + 1)
        level += 1

    x = tile_index - level
    y = level

    return x, y


def coordinates_to_tile_index(x: int, y: int) -> int:
    total_tiles = 0
    for level in range(y):
        total_tiles += (2 * level + 1)

    return total_tiles + (x + y)


def calculate_distance(tile_index: int) -> float:
    x, y = get_tile_coordinates(tile_index)

    return sqrt(x**2 + y**2)


def score_tile(player: Player, tile: Tile, inventory: Inventory) -> int:
    score = 0

    if tile.inventory.food >= inventory.food:
        score += tile.inventory.food

    if player.mode == "evil":
        return score

    i = 1
    for stone_type in StoneType:
        tile_stone_amount = tile.inventory.stones.get_amount(stone_type)
        searched_stone_amount = inventory.stones.get_amount(stone_type)

        score += min(tile_stone_amount, searched_stone_amount)
        if i > 3:
            score *= (i ** 2)
        if i == 6:
            score *= 10
        i += 1

    return score


def sort_tiles_by_resources_and_distance(player: Player, tiles: List[Tile], inventory: Inventory) -> List[Tile]:
    scored_tiles = []
    for index, tile in enumerate(tiles[1:], start=1):
        score = score_tile(player, tile, inventory)
        distance = calculate_distance(index)
        scored_tiles.append((score, distance, tile))
        Logger.log(ID="debug", message=f"Tile {index} -> Score: {score}, Distance: {distance}")

    scored_tiles.sort(key=lambda x: (-x[0], x[1]))

    sorted_tiles = [tile for _, _, tile in scored_tiles]
    return sorted_tiles


def move_towards_tile(player: Player, target_coordinates: Tuple[int, int], tiles: List[Tile]) -> None:
    target_x, target_y = target_coordinates
    player_x, player_y = 0, 0

    while player_y != target_y:
        player.move()
        player_y += 1

        current_tile_idx = coordinates_to_tile_index(player_x, player_y)
        current_tile = tiles[current_tile_idx]
        if current_tile_idx != 0:
            for _ in range(current_tile.inventory.food):
                player.take_object("food")
            for stone, amount in get_needed_stones(player, current_tile.inventory.stones).items():
                for _ in range(amount):
                    player.take_object(str(stone))
                    player.inventory.stones.add(stone)

    if target_x > player_x:
        player.turn_right()
    elif target_x < player_x:
        player.turn_left()

    offset = 1 if target_x > player_x else -1
    while player_x != target_x:
        player.move()
        player_x += offset

        current_tile_idx = coordinates_to_tile_index(player_x, player_y)
        current_tile = tiles[current_tile_idx]
        if current_tile_idx != 0:
            for _ in range(current_tile.inventory.food):
                player.take_object("food")
            for stone, amount in get_needed_stones(player, current_tile.inventory.stones).items():
                for _ in range(amount):
                    player.take_object(str(stone))
                    player.inventory.stones.add(stone)


def targeted_move(world_state: WorldState) -> None:
    try:
        player: Player = world_state.get("player")
        tiles = world_state.get("tiles")

        inventory = Inventory()
        inventory.stones = full_stones_level.stones.compare(player.inventory.stones)
        inventory.food = 1

        sorted_tiles = sort_tiles_by_resources_and_distance(player, tiles, inventory)
        target_tile = sorted_tiles[0]
        target_index = tiles.index(target_tile)
        target_coordinates = get_tile_coordinates(target_index)

        move_towards_tile(player, target_coordinates, tiles)

    except Exception as e:
        Logger.log(ID="error", message=f"An error happened while trying to move: {e}")
