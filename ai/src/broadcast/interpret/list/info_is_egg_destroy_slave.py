from src.player.player import Player


def info_is_egg_destroy_slave(player: Player, data: dict):
    if player.world_state.get("is_leader"):
        return
    if player.world_state.get("is_food_production_slave"):
        return
    if not data.get("set_egg_destroy_slave"):
        return
    player.world_state.set("is_egg_destroy_slave", True)
