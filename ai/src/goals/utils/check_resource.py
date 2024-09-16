from src.goap.worldstate import WorldState
from src.utils.logger import Logger


def check_food_in_inventory_is_higher_eq(world_state: WorldState, food_count: int) -> bool:
    try:
        player_food: int = world_state.get("player_food")
        return player_food >= food_count
    except Exception as e:
        Logger.log(ID="error", message=f"An error happened while checking for food value in inventory: {e}")
        return False


def check_food_in_inventory_is_lower(world_state: WorldState, food_count: int) -> bool:
    try:
        player_food: int = world_state.get("player_food")
        return player_food < food_count
    except Exception as e:
        Logger.log(ID="error", message=f"An error happened while checking for food value in inventory: {e}")
        return False


def check_food_in_inventory_is_lower_eq(world_state: WorldState, food_count: int) -> bool:
    try:
        player_food: int = world_state.get("player_food")
        return player_food <= food_count
    except Exception as e:
        Logger.log(ID="error", message=f"An error happened while checking for food value in inventory: {e}")
        return False


def check_food_in_inventory_increased(world_state: WorldState) -> bool:
    try:
        base_player_food: int = world_state.get("player").inventory.food
        player_food: int = world_state.get("player_food")
        return player_food > base_player_food
    except Exception as e:
        Logger.log(ID="error", message=f"An error happened while checking for food increasing in inventory: {e}")
        return False


def check_resource_in_inventory_increased(world_state: WorldState, type: str) -> bool:
    try:
        if type == "food":
            return check_food_in_inventory_increased(world_state)
        result = check_resource_in_inventory_increased(world_state, type)
        return result
    except Exception as e:
        Logger.log(ID="error", message=f"An error happened while checking for resource increasing in inventory: {e}")
        return False
