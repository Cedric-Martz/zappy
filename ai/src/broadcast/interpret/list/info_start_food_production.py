from src.player.player import Player


def info_start_food_production(player: Player, data: dict):
    if player.world_state.get("is_leader"):
        return
    if player.world_state.get("is_egg_destroy_slave"):
        return
    if not data.get("set_food_production_slave"):
        return
    player.world_state.set("is_food_production_slave", True)
