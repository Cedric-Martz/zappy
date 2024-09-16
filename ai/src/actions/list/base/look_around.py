from src.goap.action import Action
from src.actions.utils.look_around import look_around


def build_look_around():
    return Action(
        name="LookAround",
        cost=1,
        preconditions={
            "know_tiles": False,
        },
        effects={
            "know_tiles": True,
            "knew_tiles_before": False,
        },
        final_effects={
            "know_tiles": True,
            "look_around": lambda world_state: look_around(world_state),
            "knew_tiles_before": False,
        }
    )
