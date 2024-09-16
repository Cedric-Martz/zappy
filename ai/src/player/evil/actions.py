from src.player.player import Player
from src.player.evil.crack import increment_crack_hash


def decrypt_message(player: Player):
    increment_crack_hash(player)


def handle_evil_actions(player: Player):
    if player.mode != "evil":
        return
    if not player.world_state.get("already_set_enemy_message") or not player.world_state.get("is_leader"):
        return

    if not player.world_state.get("started_cracking"):
        player.world_state.set("started_cracking", True)

    if not player.world_state.get("found_enemy_key"):
        decrypt_message(player)
