from src.player.player import Player


def check_leader_should_continue_elevation(player: Player, data: dict):
    if not player.world_state.get("is_leader"):
        return
    if not data.get("leader_should_continue_elevation"):
        return
    player.world_state.set("should_complete_elevation", True)
