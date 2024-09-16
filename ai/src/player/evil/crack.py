from itertools import product, islice
from src.broadcast.encryption.decrypt_data import decrypt_data
from src.player.player import Player
from src.utils.logger import Logger


def increment_crack_hash(player: Player):
    encoded_message = player.world_state.get("enemy_message")

    if not player.world_state.get("world_list_dictionary_loaded"):
        path_to_wordlist = player.world_state.get("world_list_dictionary_path")
        try:
            dictionary = set(line.strip() for line in open(path_to_wordlist))
            player.world_state.set("world_list_dictionary", list(dictionary))
            player.world_state.set("world_list_dictionary_loaded", True)
        except FileNotFoundError as e:
            Logger.log(ID="error", message=f"Error - {e}")
            player.world_state.set("world_list_dictionary", [])
            player.world_state.set("world_list_dictionary_loaded", False)
            return

    word_list_dictionary = player.world_state.get("world_list_dictionary")
    crack_position = player.world_state.get("crack_position")
    if crack_position < len(word_list_dictionary):
        for i in range(crack_position, min(crack_position + 10, len(word_list_dictionary))):
            teamname = word_list_dictionary[i]
            try:
                data = decrypt_data(encoded_message, teamname)
                if isinstance(data, dict):
                    player.world_state.set("found_enemy_key", True)
                    player.world_state.set("enemy_key", teamname)
                    Logger.log(ID="evil", message=f"Name of the team is {teamname}")
                    return
            except Exception:
                pass
        player.world_state.set("crack_position", crack_position + 10)
        return

    crack_hash_bruteforce_step(player, encoded_message)


def crack_hash_bruteforce_step(player: Player, encoded_message: str):
    alphabet = player.world_state.get("checked_char_list")
    hash_length = player.world_state.get("hash_length")
    alphabet_position = player.world_state.get("crack_alphabet_position")

    if not player.world_state.contains('max_combinations') or player.world_state.get("hash_length") != hash_length:
        max_combinations = len(alphabet) ** hash_length
        player.world_state.set("max_combinations", max_combinations)
    else:
        max_combinations = player.world_state.get("max_combinations")

    start_index = alphabet_position
    end_index = start_index + 10

    for combo in islice(product(alphabet, repeat=hash_length), start_index, end_index):
        teamname = ''.join(combo)
        try:
            Logger.log(ID="evil", message=f"Testing with : {teamname}", end='\r')
            data = decrypt_data(encoded_message, teamname)
            Logger.log(ID="evil", message=f"data is : {data}")
            if isinstance(data, dict):
                player.world_state.set("found_enemy_key", True)
                player.world_state.set("enemy_key", teamname)
                Logger.log(ID="evil", message=f"Name of the team is {teamname}")
                return
        except Exception:
            pass

    player.world_state.set("crack_alphabet_position", end_index)

    if end_index >= len(alphabet) ** hash_length:
        player.world_state.set("hash_length", hash_length + 1)
        player.world_state.set("crack_alphabet_position", 0)
        player.world_state.set("max_combinations", len(alphabet) ** (hash_length + 1))
