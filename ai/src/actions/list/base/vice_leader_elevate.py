from src.goap.action import Action


def build_vice_leader_elevate():
    return Action(
        name="Vice leader elevate",
        cost=0,
        preconditions={
            "is_vice_leader": True,
            "vice_leader_check": True,
        },
        effects={
            "vice_leader_elevated": True,
        },
        final_effects={
            "vice_leader_elevated": True,
            "elevate": lambda world_state: world_state.get("player").start_incantation(),
        }
    )
