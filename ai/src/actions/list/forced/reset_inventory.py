from src.goap.action import Action


def build_reset_inventory():
    return Action(
        name="Reset inventory",
        cost=0,
        preconditions={
            "check_action_count": lambda world_state: world_state.get("action_count") > 5,
        },
        effects={},
        final_effects={
            "know_inventory": False,
            "action_count": 0,
        }
    )
