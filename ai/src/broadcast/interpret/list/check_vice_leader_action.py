from src.player.player import Player


def check_vice_leader_action(player: Player, data: dict):
    if not player.world_state.get("is_vice_leader"):
        return
    if not data.get("vice_leader_action"):
        return
    player.world_state.set("vice_leader_check", True)
