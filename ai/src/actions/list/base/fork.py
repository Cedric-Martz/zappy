from src.goap.action import Action
from src.goals.utils.check_resource import check_food_in_inventory_is_higher_eq
from src.actions.utils.execute_fork import execute_fork


def build_fork():
    return Action(
        name="Fork",
        cost=0,
        preconditions={
            "is_leader": True,
            "has_enough_stones_to_finish": True,
            "food_production_fork_done": True,
            "check_fork_remaining": lambda world_state: world_state.get("fork_remaining") > 0,
            "check_food": lambda world_state: check_food_in_inventory_is_higher_eq(world_state, 10),
            "waiting_for_normal_player_info": False,
        },
        effects={
            "forked": True,
            "set_fork_remaining": lambda world_state: world_state.set("fork_remaining", world_state.get("fork_remaining") - 1),
            "waiting_for_normal_player_info": True,
        },
        final_effects={
            "forked": True,
            "fork": lambda world_state: execute_fork(world_state),
            "set_fork_remaining": lambda world_state: world_state.set("fork_remaining", world_state.get("fork_remaining") - 1),
            "waiting_for_normal_player_info": True,
        }
    )


def build_fork_food_production():
    return Action(
        name="Fork to produce food",
        cost=0,
        preconditions={
            "check_destroy_eggs_fork_done": lambda world_state: world_state.get("is_food_production_slave") or (world_state.get("is_leader") and world_state.get("destroy_eggs_fork_done")),
            "food_production_fork_done": False,
            "can_fork": lambda world_state: world_state.get("is_leader") or world_state.get("is_food_production_slave"),
            "check_fork_remaining": lambda world_state: world_state.get("fork_remaining") > 0,
        },
        effects={
            "forked": True,
            "set_fork_remaining": lambda world_state: world_state.set("fork_remaining", world_state.get("fork_remaining") - 1),
        },
        final_effects={
            "forked": True,
            "fork": lambda world_state: execute_fork(world_state),
            "set_fork_remaining": lambda world_state: world_state.set("fork_remaining", world_state.get("fork_remaining") - 1),
        }
    )


def build_fork_destroy_eggs():
    return Action(
        name="Fork to destroy eggs",
        cost=0,
        preconditions={
            "destroy_eggs_fork_done": False,
            "can_fork": lambda world_state: (world_state.get("is_leader") and world_state.get("level") == 2) or world_state.get("is_egg_destroy_slave"),
            "check_fork_remaining": lambda world_state: world_state.get("fork_remaining") > 0,
            "check_food": lambda world_state: world_state.get("is_egg_destroy_slave") or check_food_in_inventory_is_higher_eq(world_state, 12),
        },
        effects={
            "forked": True,
            "set_fork_remaining": lambda world_state: world_state.set("fork_remaining", world_state.get("fork_remaining") - 1),
        },
        final_effects={
            "forked": True,
            "fork": lambda world_state: execute_fork(world_state),
            "set_fork_remaining": lambda world_state: world_state.set("fork_remaining", world_state.get("fork_remaining") - 1),
        }
    )
