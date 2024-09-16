from src.goap.action import Action
from src.actions.utils.check_resource import check_resource
from src.actions.utils.harvest_resource import harvest_resource
from src.actions.utils.check_useful_resource import check_useful_resource


def build_harvest_action(stone_type: str) -> Action:
    return Action(
        name=f"Harvest{stone_type.capitalize()}",
        cost=1,
        preconditions={
            "has_enough_stones_to_finish": False,
            "know_tiles": True,
            f"{stone_type}_on_tile": lambda world_state: check_resource(world_state, stone_type),
            f"need_{stone_type}": lambda world_state: check_useful_resource(world_state, stone_type)
        },
        effects={
            f"harvest_{stone_type}": lambda world_state: harvest_resource(world_state, stone_type),
            "harvested_useful_resource": True
        },
        final_effects={
            f"harvest_{stone_type}": lambda world_state: harvest_resource(world_state, stone_type, True),
            "harvested_useful_resource": True
        }
    )
