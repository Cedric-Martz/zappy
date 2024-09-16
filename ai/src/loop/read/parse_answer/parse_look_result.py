from typing import List
from src.data.stones import Stones
from src.data.tile import Tile


def parse_look_result(look_result: str) -> List[Tile]:
    tiles_info = look_result.strip('[]').split(',')

    parsed_tiles = []
    for tile_info in tiles_info:
        tile_info = tile_info.strip()
        items = tile_info.split()

        stones = Stones(
            linemate=items.count("linemate"),
            deraumere=items.count("deraumere"),
            sibur=items.count("sibur"),
            mendiane=items.count("mendiane"),
            phiras=items.count("phiras"),
            thystame=items.count("thystame")
        )

        food = items.count("food")
        players = items.count("player")

        parsed_tiles.append(Tile(stones=stones, food=food, players=players))

    return parsed_tiles
