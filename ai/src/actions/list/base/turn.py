from src.goap.action import Action
from src.actions.utils.turn_randomly import turn_randomly
from src.actions.utils.should_move import should_not_move


def build_turn_no_useful_resource():
    return Action(
        name="Turn to search for useful resources",
        cost=2,
        preconditions={
            "know_tiles": True,
            "check_no_useful_resource": lambda world_state: should_not_move(world_state),
        },
        effects={
            "turned": True,
            "know_tiles": False,
        },
        final_effects={
            "turn": lambda world_state: turn_randomly(world_state),
            "know_tiles": False,
        }
    )
