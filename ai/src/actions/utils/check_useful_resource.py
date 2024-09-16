from src.goap.worldstate import WorldState
from src.data.stone_type import StoneType
from src.data.values_by_level import full_stones_level
from src.utils.logger import Logger


def check_useful_stone(world_state: WorldState, stone_type: StoneType) -> bool:
    try:
        current_stones = world_state.get("player").inventory.stones
        total_stone_value = full_stones_level.stones

        return total_stone_value.compare(current_stones).get_amount(stone_type) > 0

    except Exception as e:
        Logger.log(ID="error", message=f"An error happened while checking for useful stones: {e}")
        return False


def check_useful_resource(world_state: WorldState, resource_type: str) -> bool:
    if StoneType.is_stone(resource_type):
        return check_useful_stone(
            world_state,
            StoneType.from_str(resource_type),
        )
    return False
