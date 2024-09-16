from src.goap.action import Action


def build_waiting_for_start_broadcast_answer():
    return Action(
        name="Waiting for start broadcast answer",
        cost=0,
        preconditions={
            "is_egg_destroy_slave": False,
            "is_food_production_slave": False,
            "start_broadcast_initialized": False,
            "already_sent_start_broadcast": True,
        },
        effects={
            "waited_for_start_broadcast_answer": True,
        },
        final_effects={
            "waited_for_start_broadcast_answer": True,
            "check_inventory": lambda world_state: world_state.get("player").check_inventory(),
        }
    )
