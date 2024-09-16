from src.goap.goal import Goal


def build_look_around():
    return Goal(
        name="Look around",
        priority=0,
        conditions={
            "knew_tiles_before": False,
            "know_tiles": True,
        }
    )
