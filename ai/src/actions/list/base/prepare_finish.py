from src.goap.action import Action
from src.data.values_by_level import full_stones_level
from src.actions.utils.drop_advanced_elevate_values import drop_advanced_elevate_values


def build_prepare_finish():
    return Action(
        name="Prepare finish",
        cost=0,
        preconditions={
            "is_leader": True,
            "destroy_eggs_fork_done": True,
            "food_production_fork_done": False,
            "currently_producing_food": False,
            "has_enough_stones_to_finish": False,
            "check_has_enough_stones_to_finish": lambda world_state: world_state.get("player").inventory.stones.compare(full_stones_level.stones).check_elevation_validity(),
        },
        effects={
            "prepared_finish": True,
            "currently_producing_food": True,
            "fork_remaining": 1,
        },
        final_effects={
            "prepared_finish": True,
            "drop_advanced_elevate_values": lambda world_state: drop_advanced_elevate_values(world_state),
            "currently_producing_food": True,
            "fork_remaining": 1,
        }
    )
