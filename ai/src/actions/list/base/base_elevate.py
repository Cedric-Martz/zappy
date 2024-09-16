from src.goap.action import Action
from src.data.stone_type import StoneType
from src.goals.utils.check_resource import check_food_in_inventory_is_higher_eq


def build_base_elevate():
    return Action(
        name="First elevate",
        cost=0,
        preconditions={
            "destroy_eggs_fork_done": False,
            "know_tiles": True,
            "know_inventory": True,
            "enough_resources_and_players_to_elevate": lambda world_state: world_state.get("tiles") and world_state.get("tiles")[0].inventory.stones.get_amount(StoneType.LINEMATE) >= 1,
            "level": 1,
            "check_food": lambda world_state: check_food_in_inventory_is_higher_eq(world_state, 10)
        },
        effects={
            "started_incantation": True,
        },
        final_effects={
            "started_incantation": True,
            "start_incantation": lambda world_state: world_state.get("player").start_incantation(),
        }
    )
