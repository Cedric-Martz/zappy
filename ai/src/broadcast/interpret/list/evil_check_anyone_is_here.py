from src.player.player import Player


def send_erroneous_messages(player: Player):
    player.broadcast_specific({
        "should_gather": True,
        "someone_is_here": True,
        "check_if_anyone_is_here": True,
        "become_vice_leader": True,
        "set_food_production_slave": True,
        "set_egg_destroy_slave": True,
        "set_fork_remaining": 42,
        "drop_all_food": True,
        "leader_should_continue_elevation": True,
        "players_should_continue_elevation": True,
        "vice_leader_action": True,
        "set_fork_lay_egg": False,
        "take_food_amount": -42,
        "tell_leader_food_is_taken": True
    }, player.world_state.get("enemy_key"))


def check_anyone_is_here(player: Player, data: dict):
    if not player.world_state.get("is_leader"):
        return
    if not data.get("check_if_anyone_is_here"):
        return

    if not player.world_state.get("destroy_eggs_fork_done"):
        player.world_state.set("destroy_eggs_fork_count_players", player.world_state.get("destroy_eggs_fork_count_players") + 1)
        if player.world_state.get("destroy_eggs_fork_count_players") == player.world_state.get("slots_available"):
            player.world_state.set("destroy_eggs_fork_done", True)
            player.world_state.set("fork_lay_egg", True)
            player.world_state.set("should_start_producing_food", True)

        player.broadcast({
            "set_egg_destroy_slave": True,
            "set_fork_remaining": 1 if not player.world_state.get("destroy_eggs_fork_done") else 0,
            "drop_all_food": True,
        })
        return

    if not player.world_state.get("currently_producing_food"):
        return
    player.world_state.set("produce_food_fork_count_players", player.world_state.get("produce_food_fork_count_players") + 1)
    player.broadcast({
        "set_food_production_slave": True,
        "set_fork_remaining": 1,
        "drop_all_food": True,
        "set_fork_lay_egg": True
    })
    if player.world_state.get("produce_food_fork_count_players") > 1:
        for _ in range(8):
            player.take_object("food")
    if player.world_state.get("found_enemy_key"):
        send_erroneous_messages(player)
