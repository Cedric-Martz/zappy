from src.goap.goal import Goal


def build_checked_start_broadcast_answer():
    return Goal(
        name="Checked start broadcast answer",
        priority=10,
        conditions={
            "start_broadcast_initialized": True,
            "just_checked_start_broadcast_answer": True,
        }
    )
