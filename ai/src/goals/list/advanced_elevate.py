from src.goap.goal import Goal


def build_advanced_elevate():
    return Goal(
        name="Advanced elevate",
        priority=60,
        conditions={
            "start_broadcast_initialized": True,
            "is_leader": True,
            "should_complete_elevation": True,
            "started_incantation": True,
        }
    )
