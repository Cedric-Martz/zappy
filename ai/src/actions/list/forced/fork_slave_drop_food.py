from src.goap.action import Action
from src.actions.utils.fork_slave_drop_food import fork_slave_drop_food


def build_fork_slave_drop_food():
    return Action(
        name="Fork slave drop food",
        cost=0,
        preconditions={
            "drop_food_on_fork": True,
            "fork_remaining": 0,
        },
        effects={},
        final_effects={
            "fork_slave_drop_food": lambda world_state: fork_slave_drop_food(world_state.get("player")),
        }
    )
