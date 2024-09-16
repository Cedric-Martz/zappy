/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** commands
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #define COMMANDS_NUMBER COMMANDS_AI + COMMANDS_GUI

    #include "ai.h"
    #include "gui.h"
    #include "debug.h"
    #define HELP "#Choose a team between : GRAPHIC / DEBUG / AI (team_name)\n"

void admin_commands(client_t *client, server_t *server);
void execute_commands(client_t *client, server_t *server);
void handle_buffer_management(char *buffer, client_t *client,
    server_t *server);
void handle_one_command(client_t *client, server_t *server);
void handle_commands(char *command, char *substring,
    client_t *client, server_t *server);
void choose_type(char *command, client_t *client, server_t *server);

struct choose_type_tab {
    const char *command;
    void (*function)(client_t *client, server_t *server);
};

    #define TYPE_NB 2

void join_graphic(client_t *client, server_t *server);
void get_help_default(client_t *client, server_t *server);

static const struct choose_type_tab type_tab[TYPE_NB] = {
    {"help", get_help_default },
    {"GRAPHIC", join_graphic },
};


enum client_type {
    None = 0,
    AI,
    GUI
};

struct commands {
    const char *command;
    const enum client_type type;
    void (*function)(char *args, client_t *client, server_t *server);
};


static const struct commands commands_tab[COMMANDS_NUMBER] = {
    // ? AI
    { "Help", AI, get_help_ai },
    { "Forward", AI, go_forward },
    { "Right", AI, go_right },
    { "Left", AI, go_left },
    { "Look", AI, look_around },
    { "Inventory", AI, show_inventory },
    { "Broadcast", AI, send_broadcast },
    { "Connect_nbr", AI, show_unused_slots },
    { "Fork", AI, fork_player },
    { "Eject", AI, eject_player },
    { "Take", AI, take_object },
    { "Set", AI, drop_object },
    { "Incantation", AI, start_incancation },
    // ? GUI
    { "help", GUI, get_help_gui },
    { "msz", GUI, get_map_size },
    { "bct", GUI, get_tile_info},
    { "mct", GUI, trigger_mct},
    { "tna", GUI, get_all_teams},
    { "ppo", GUI, get_player_position},
    { "plv", GUI, get_player_level},
    { "pin", GUI, get_player_inventory},
    { "sgt", GUI, time_request},
    { "sst", GUI, time_change},
};

struct admin {
    const char *command;
    void (*function)(char *args, client_t *client, server_t *server);
};

static const struct admin admin_tab[COMMANDS_DEBUG] = {
    // ? DEBUG
    { "/help", get_help_debug },
    { "/clients", list_clients },
    { "/send_ais", send_msg_ais },
    { "/send_guis", send_msg_guis },
    { "/set_inventory", set_inventory },
    { "/tp", tp_player },
    { "/kill", kill_player },
    { "/set_level", set_level },
    { "/quit", quit_server },
    { "/clear", clear_terminal },
    { "/pause", pause_world },
    { "/play", play_world },
    { "/restart", restart_world },
    { "/set_teams_slots", set_teams_slots },
    { "/set_freq", set_freq },
    { "/no_refill", set_refill },
    { "/no_food", set_food },
    { "/set_tile", set_tile },
    { "/clear_tile", clear_tile },
    { "/fork", simulate_fork },
    { "/incantate", simulate_incantation },
    { "/broadcast", simulate_broadcast },
    { "/set_logger_output", set_file_output}
};

#endif /* !COMMANDS_H_ */
