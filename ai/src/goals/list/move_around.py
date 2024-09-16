from src.goap.goal import Goal


def build_move_around():
    return Goal(
        name="Move around",
        priority=3,
        conditions={
            "is_leader": True,
            "start_broadcast_initialized": True,
            "has_enough_stones_to_finish": False,
            "currently_producing_food": False,
            "moved": True,
        }
    )
