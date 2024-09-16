from src.player.player import Player


def check_set_fork_lay_egg(player: Player, data: dict):
    if player.world_state.get("is_leader"):
        return
    if not data.get("set_fork_lay_egg"):
        return
    player.world_state.set("fork_lay_egg", True)
