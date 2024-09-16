from src.player.player import Player


def info_someone_is_here(player: Player, data: dict):
    if player.world_state.get("received_start_broadcast_answer"):
        return
    if not data.get("someone_is_here"):
        return
    player.world_state.set("received_start_broadcast_answer", True)
