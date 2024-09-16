from src.goap.goal import Goal


def build_harvest_useful_resource():
    return Goal(
        name="Harvest useful resource",
        priority=5,
        conditions={
            "is_leader": True,
            "start_broadcast_initialized": True,
            "has_enough_stones_to_finish": False,
            "currently_producing_food": False,
            "harvested_useful_resource": True
        }
    )
