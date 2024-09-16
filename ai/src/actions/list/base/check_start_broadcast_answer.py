from src.goap.action import Action


def build_check_start_broadcast_answer():
    return Action(
        name="Check start broadcast answer",
        cost=0,
        preconditions={
            "is_egg_destroy_slave": False,
            "is_food_production_slave": False,
            "start_broadcast_initialized": False,
            "just_checked_start_broadcast_answer": False,
            "received_start_broadcast_answer": True,
        },
        effects={
            "just_checked_start_broadcast_answer": True,
            "start_broadcast_initialized": True,
        },
        final_effects={
            "just_checked_start_broadcast_answer": True,
            "start_broadcast_initialized": True,
        }
    )


def build_check_no_start_broadcast_answer():
    return Action(
        name="Check no start broadcast answer",
        cost=0,
        preconditions={
            "is_egg_destroy_slave": False,
            "is_food_production_slave": False,
            "start_broadcast_initialized": False,
            "know_inventory": True,
            "just_checked_start_broadcast_answer": False,
            "check_food_reduced": lambda world_state: world_state.get("player").inventory.food <= 7,
        },
        effects={
            "just_checked_start_broadcast_answer": True,
            "is_leader": True,
            "set_fork_remaining": lambda world_state: world_state.set("fork_remaining", 1 if world_state.get("slots_available") else 0),
            "start_broadcast_initialized": True,
        },
        final_effects={
            "just_checked_start_broadcast_answer": True,
            "is_leader": True,
            "set_fork_remaining": lambda world_state: world_state.set("fork_remaining", 1 if world_state.get("slots_available") else 0),
            "start_broadcast_initialized": True,
        }
    )
