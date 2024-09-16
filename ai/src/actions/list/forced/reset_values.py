from src.goap.action import Action


def build_reset_values():
    return Action(
        name="Reset values",
        cost=0,
        preconditions={},
        effects={},
        final_effects={
            "moved": False,
            "turned": False,
            "reset_player_food": lambda world_state: world_state.set("player_food", world_state.get("player").inventory.food),
            "harvested_useful_resource": False,
            "moved_towards_goal": False,
            "waited_for_elevation": False,
            "waited_for_start_broadcast_answer": False,
            "just_checked_start_broadcast_answer": False,
            "forked": lambda world_state: world_state.set("forked", world_state.get("forked") if world_state.get("is_egg_destroy_slave") or world_state.get("is_food_production_slave") else False),
            "prepared_finish": False,
            "vice_leader_elevated": False,
        }
    )
