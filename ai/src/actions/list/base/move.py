from src.goap.action import Action
from src.actions.utils.targeted_move import targeted_move
from src.actions.utils.should_move import should_move


def build_move():
    return Action(
        name="Move towards resources",
        cost=5,
        preconditions={
            "know_tiles": True,
            "know_inventory": True,
            "should_move": lambda world_state: should_move(world_state),
        },
        effects={
            "know_tiles": False,
            "moved": True,
        },
        final_effects={
            "move": lambda world_state: targeted_move(world_state),
            "moved": True,
            "know_tiles": False,
        }
    )
