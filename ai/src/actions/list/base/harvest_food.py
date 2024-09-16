from src.goap.action import Action
from src.actions.utils.check_resource import check_resource
from src.actions.utils.harvest_resource import harvest_resource


def build_harvest_food():
    return Action(
        name="HarvestFood",
        cost=0,
        preconditions={
            "know_tiles": True,
            "food_on_tile": lambda world_state: check_resource(world_state, "food"),
        },
        effects={
            "harvest_food": lambda world_state: harvest_resource(world_state, "food"),
            "harvested_useful_resource": True
        },
        final_effects={
            "harvest_food": lambda world_state: harvest_resource(world_state, "food", True),
            "harvested_useful_resource": True
        }
    )
