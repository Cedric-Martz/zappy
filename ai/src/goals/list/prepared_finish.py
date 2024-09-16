from src.goap.goal import Goal


def build_prepared_finish():
    return Goal(
        name="Prepared finish",
        priority=50,
        conditions={
            "is_leader": True,
            "prepared_finish": True,
        }
    )
