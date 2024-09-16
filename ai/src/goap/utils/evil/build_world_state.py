from src.goap.worldstate import WorldState
from uuid import UUID


def build_world_state(player, uuid: UUID):
    world_state = WorldState()

    world_state.set("player", player)
    world_state.set("alive", True)
    world_state.set("level", 1)
    world_state.set("moved", False)
    world_state.set("player_food", player.inventory.food)
    world_state.set("know_tiles", False)
    world_state.set("know_inventory", False)
    world_state.set("moved_towards_goal", False)

    world_state.set("welcomed", False)
    world_state.set("logged_in", False)
    world_state.set("uuid", uuid)

    world_state.set("slots_available", -1)
    world_state.set("map_size", (-1, -1))
    world_state.set("tiles", [])

    world_state.set("start_broadcast_initialized", False)
    world_state.set("just_sent_start_broadcast", False)
    world_state.set("already_sent_start_broadcast", False)
    world_state.set("waited_for_start_broadcast_answer", False)
    world_state.set("just_checked_start_broadcast_answer", False)
    world_state.set("received_start_broadcast_answer", False)

    world_state.set("action_count", 0)
    world_state.set("turn_direction", "none")
    world_state.set("turn_count", 0)

    world_state.set("destroy_eggs_fork_count_players", 0)
    world_state.set("destroy_eggs_fork_done", False)
    world_state.set("is_egg_destroy_slave", False)

    world_state.set("should_start_producing_food", False)
    world_state.set("currently_producing_food", False)
    world_state.set("produce_food_fork_count_players", 0)
    world_state.set("is_food_production_slave", False)
    world_state.set("food_production_fork_done", False)
    world_state.set("drop_food_on_fork", False)

    world_state.set("has_enough_stones_to_finish", False)

    world_state.set("is_leader", False)
    world_state.set("fork_remaining", 0)
    world_state.set("fork_lay_egg", False)
    world_state.set("forked", False)

    world_state.set("already_set_enemy_message", False)
    world_state.set("enemy_message", "")
    world_state.set("started_cracking", False)
    world_state.set("crack_position", 0)
    world_state.set("crack_alphabet_position", 0)
    world_state.set("hash_length", 1)
    world_state.set("found_enemy_key", False)
    world_state.set("enemy_key", "")
    world_state.set("checked_char_list", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")

    world_state.set("world_list_dictionary_path", "wordlist/wordlist.txt")
    world_state.set("world_list_dictionary_loaded", False)
    world_state.set("world_list_dictionary", [])

    return world_state
