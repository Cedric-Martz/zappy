from src.goap.action import Action


def build_check_vice_leader():
    return Action(
        name="Check vice leader",
        cost=0,
        preconditions={
            "is_leader": True,
            "food_production_fork_done": True,
            "has_enough_stones_to_finish": True,
            "food_distributed": True,
            "fork_remaining": 0,
            "vice_leader_check": False,
        },
        effects={},
        final_effects={
            "vice_leader_check": True,
            "send_broadcast": lambda world_state: world_state.get("player").broadcast({"vice_leader_action": True, "players_should_continue_elevation": True}),
        }
    )
