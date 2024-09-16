from src.goap.action import Action


def build_wait_for_elevation():
    return Action(
        name="Wait for elevation",
        cost=0,
        preconditions={
            "is_leader": False,
            "is_vice_leader": False,
            "should_complete_elevation": True,
        },
        effects={
            "waited_for_elevation": True
        },
        final_effects={
            "waited_for_elevation": True
        }
    )
