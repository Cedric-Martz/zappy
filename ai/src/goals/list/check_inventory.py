from src.goap.goal import Goal


def build_check_inventory():
    return Goal(
        name="Check inventory",
        priority=10,
        conditions={
            "know_inventory": True,
        }
    )
