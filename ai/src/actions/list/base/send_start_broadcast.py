from src.goap.action import Action


def build_send_start_broadcast():
    return Action(
        name="Send start broadcast",
        cost=0,
        preconditions={
            "start_broadcast_initialized": False,
            "already_sent_start_broadcast": False,
        },
        effects={
            "just_sent_start_broadcast": True,
        },
        final_effects={
            "just_sent_start_broadcast": True,
            "send_start_broadcast": lambda world_state: world_state.get("player").broadcast({"check_if_anyone_is_here": True}),
        }
    )
