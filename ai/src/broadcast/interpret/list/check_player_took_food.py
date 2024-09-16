from src.player.player import Player


def check_player_took_food(player: Player, data: dict):
    if not player.world_state.get("is_leader"):
        return
    if not data.get("tell_leader_food_is_taken"):
        return
    player.world_state.set("food_taken_count", player.world_state.get("food_taken_count") + 1)
    if player.world_state.get("food_taken_count") == 5:
        player.world_state.set("food_distributed", True)
