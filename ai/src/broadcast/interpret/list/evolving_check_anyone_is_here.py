from src.player.player import Player


def check_anyone_is_here(player: Player, data: dict):
    if not player.world_state.get("is_leader"):
        return
    if not data.get("check_if_anyone_is_here"):
        return

    if not player.world_state.get("destroy_eggs_fork_done"):
        player.world_state.set("destroy_eggs_fork_count_players", player.world_state.get("destroy_eggs_fork_count_players") + 1)
        if player.world_state.get("destroy_eggs_fork_count_players") >= player.world_state.get("slots_available"):
            player.world_state.set("destroy_eggs_fork_done", True)
            player.world_state.set("fork_lay_egg", True)
        player.broadcast({
            "set_egg_destroy_slave": True,
            "set_fork_remaining": 1 if not player.world_state.get("destroy_eggs_fork_done") else 0,
            "drop_all_food": True,
        })
        return

    if not player.world_state.get("food_production_fork_done"):
        player.world_state.set("produce_food_fork_count_players", player.world_state.get("produce_food_fork_count_players") + 1)
        if player.world_state.get("produce_food_fork_count_players") >= player.world_state.get("food_production_slave_amount"):
            player.world_state.set("food_production_fork_done", True)
            player.world_state.set("currently_producing_food", False)
            player.world_state.set("has_enough_stones_to_finish", True)
            player.world_state.set("fork_remaining", 5)

        player.broadcast({
            "set_food_production_slave": True,
            "set_fork_remaining": 1 if not player.world_state.get("food_production_fork_done") else 0,
            "drop_all_food": True,
            "set_fork_lay_egg": not player.world_state.get("food_production_fork_done"),
        })
        if player.world_state.get("food_production_fork_done"):
            for _ in range(10):
                player.take_object("food")
        if not player.world_state.get("food_production_fork_done") and player.world_state.get("produce_food_fork_count_players") > 1:
            for _ in range(2):
                player.take_object("food")
        return

    if not player.world_state.get("already_set_vice_leader"):
        player.broadcast({"become_vice_leader": True})
        player.world_state.set("already_set_vice_leader", True)

    player.broadcast({
        "someone_is_here": True,
        "take_food_amount": player.world_state.get("end_player_food_amount")
    })
    player.world_state.set("waiting_for_normal_player_info", False)
