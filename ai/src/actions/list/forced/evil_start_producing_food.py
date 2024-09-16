from src.goap.action import Action


def build_evil_start_producing_food():
    return Action(
        name="Evil AI start producing food",
        cost=0,
        preconditions={
            "should_start_producing_food": True,
        },
        effects={},
        final_effects={
            "should_start_producing_food": False,
            "currently_producing_food": True,
            "fork_remaining": 1,
        }
    )
