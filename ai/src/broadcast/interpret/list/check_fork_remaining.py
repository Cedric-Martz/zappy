from src.player.player import Player


def check_fork_remaining(player: Player, data: dict):
    if player.world_state.get("is_leader"):
        return
    if player.world_state.get("forked"):
        return
    fork_remaining = data.get("set_fork_remaining")
    if fork_remaining is None:
        return
    if player.world_state.get("is_egg_destroy_slave") and fork_remaining == 0:
        player.world_state.set("forked", True)
        return

    player.world_state.set("fork_remaining", fork_remaining)
