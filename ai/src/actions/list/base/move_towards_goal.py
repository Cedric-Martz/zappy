from src.goap.action import Action
from src.actions.utils.move_towards_goal import move_towards_goal
from src.actions.utils.should_move_towards_goal import should_move_towards_goal


def build_move_towards_goal():
    return Action(
        name="Move towards goal",
        cost=1,
        preconditions={
            "should_move_towards_goal": lambda world_state: should_move_towards_goal(world_state),
        },
        effects={
            "know_tiles": False,
            "moved_towards_goal": True,
        },
        final_effects={
            "move_towards_goal": lambda world_state: move_towards_goal(world_state),
            "moved_towards_goal": True,
            "know_tiles": False,
        }
    )
