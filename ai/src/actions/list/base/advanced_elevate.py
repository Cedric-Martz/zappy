from src.goap.action import Action
from src.actions.utils.start_incantation import start_incantation


def build_advanced_elevate():
    return Action(
        name="Advanced elevate",
        cost=0,
        preconditions={
            "is_leader": True,
            "should_complete_elevation": True,
        },
        effects={
            "started_incantation": True
        },
        final_effects={
            "started_incantation": True,
            "start_incantation": lambda world_state: start_incantation(world_state),
        }
    )
