from src.goap.goal import Goal


def build_vice_leader_elevated():
    return Goal(
        name="Vice leader elevated",
        priority=55,
        conditions={
            "is_vice_leader": True,
            "vice_leader_elevated": True,
        }
    )
