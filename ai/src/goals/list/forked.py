from src.goap.goal import Goal


def build_forked():
    return Goal(
        name="Forked",
        priority=35,
        conditions={
            "forked": True,
        }
    )
