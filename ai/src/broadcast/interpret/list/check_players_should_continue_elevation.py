from src.player.player import Player


def check_players_should_continue_elevation(player: Player, data: dict):
    if player.world_state.get("is_leader"):
        return
    if not data.get("players_should_continue_elevation"):
        return
    player.world_state.set("should_complete_elevation", True)
