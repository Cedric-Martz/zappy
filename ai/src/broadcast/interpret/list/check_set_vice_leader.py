from src.player.player import Player


def check_set_vice_leader(player: Player, data: dict):
    if player.world_state.get("is_leader"):
        return
    if not data.get("become_vice_leader"):
        return
    player.world_state.set("is_vice_leader", True)
