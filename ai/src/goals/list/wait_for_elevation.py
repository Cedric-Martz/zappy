from src.goap.goal import Goal


def build_wait_for_elevation():
    return Goal(
        name="Wait for elevation",
        priority=20,
        conditions={
            "is_leader": False,
            "start_broadcast_initialized": True,
            "waited_for_elevation": True
        }
    )
