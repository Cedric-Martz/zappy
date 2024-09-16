from src.goap.goal import Goal


def build_moved_towards_goal():
    return Goal(
        name="Moved towards goal",
        priority=30,
        conditions={
            "is_leader": True,
            "start_broadcast_initialized": True,
            "has_enough_stones_to_finish": False,
            "currently_producing_food": False,
            "at_goal": False,
            "moved_towards_goal": True,
        }
    )
