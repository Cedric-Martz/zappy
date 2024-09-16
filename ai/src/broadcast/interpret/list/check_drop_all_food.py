from src.player.player import Player


def check_drop_all_food(player: Player, data: dict):
    if player.world_state.get("is_leader"):
        return
    if not data.get("drop_all_food"):
        return
    player.world_state.set("drop_food_on_fork", True)
