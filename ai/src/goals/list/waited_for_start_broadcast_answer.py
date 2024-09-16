from src.goap.goal import Goal


def build_waited_for_start_broadcast_answer():
    return Goal(
        name="Waited for start broadcast answer",
        priority=5,
        conditions={
            "start_broadcast_initialized": False,
            "already_sent_start_broadcast": True,
            "waited_for_start_broadcast_answer": True,
        }
    )
