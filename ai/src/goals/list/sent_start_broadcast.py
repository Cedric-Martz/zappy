from src.goap.goal import Goal


def build_sent_start_broadcast():
    return Goal(
        name="Sent start broadcast",
        priority=10,
        conditions={
            "start_broadcast_initialized": False,
            "just_sent_start_broadcast": True,
            "already_sent_start_broadcast": False
        }
    )
