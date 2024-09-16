from src.goap.action import Action


def build_check_start_broadcast():
    return Action(
        name="Check start broadcast",
        cost=0,
        preconditions={
            "just_sent_start_broadcast": True,
        },
        effects={},
        final_effects={
            "already_sent_start_broadcast": True,
            "just_sent_start_broadcast": False,
        }
    )
