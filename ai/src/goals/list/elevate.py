from src.goap.goal import Goal


def build_elevate():
    return Goal(
        name="Elevate",
        priority=20,
        conditions={
            "is_leader": True,
            "start_broadcast_initialized": True,
            "has_enough_stones_to_finish": False,
            "food_production_fork_done": False,
            "know_tiles": True,
            "know_inventory": True,
            "started_incantation": True,
        }
    )
