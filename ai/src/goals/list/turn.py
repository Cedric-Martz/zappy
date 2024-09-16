from src.goap.goal import Goal


def build_turn():
    return Goal(
        name="Turn",
        priority=1,
        conditions={
            "is_leader": True,
            "start_broadcast_initialized": True,
            "has_enough_stones_to_finish": False,
            "currently_producing_food": False,
            "turned": True,
        }
    )
