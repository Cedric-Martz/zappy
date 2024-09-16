from src.data.stones import Stones
from src.data.tile import Tile
from src.data.values_by_level import ValuesByLevel, values_by_level
from src.goap.worldstate import WorldState
from src.utils.logger import Logger


def check_elevate_values(world_state: WorldState) -> bool:
    try:
        player = world_state.get("player")
        player_level: int = player.world_state.get("level")
        current_stones: Stones = player.inventory.stones
        current_food: int = player.inventory.food
        if not world_state.get("tiles"):
            return False
        current_tile: Tile = world_state.get("tiles")[0]

        if player_level not in values_by_level:
            return False

        required_values: ValuesByLevel = values_by_level[player_level]
        required_stones: Stones = required_values.stones
        required_players: int = required_values.players

        if current_food < 9:
            return False

        if not current_stones.compare(required_stones).check_elevation_validity():
            return False

        if current_tile.players < required_players:
            return False

        return True
    except Exception as e:
        Logger.log(ID="error", message=f"An error happened while checking for elevate values: {e}")
        return False
