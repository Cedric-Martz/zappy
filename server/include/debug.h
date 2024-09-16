/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** debug
*/

#ifndef DEBUG_H_
    #define DEBUG_H_

    #include "logger.h"
    #define COMMANDS_DEBUG 23
    #define HELP_TAB_DEBUG (COMMANDS_DEBUG) * 2


static const char *const command_info_debug[HELP_TAB_DEBUG] = {
    "/clients player_id*",
    "   → list all connected clients",
    "/send_ais msg",
    "   → send a message to all AIs",
    "/send_guis msg",
    "   → send a message to all GUIs",
    "/set_inventory player_id resource quantity",
    "   → set the quantity of a given resource in the inventory",
    "/tp player_id x y",
    "   → teleport a player to a tile",
    "/kill player_id",
    "   → kill a player",
    "/set_level player_id level",
    "   → set the level of a player",
    "/quit",
    "   → stop the server",
    "/clear",
    "   → clear the shell",
    "/pause",
    "   → pause the event loop",
    "/play",
    "   → start the event loop",
    "/restart",
    "   → restart the world",
    "/set_teams_slots team_name value",
    "   → change the number of available slots for a team",
    "/set_freq value",
    "   → change the refresh rate",
    "/no_refill true/false",
    "   → enable/disable world refill",
    "/no_food true/false",
    "   → enable/disable food management",
    "/set_tile x y resource quantity",
    "   → set the quantity of a resource on a tile",
    "/clear_tile x y resource",
    "   → clear a resource on a tile",
    "/fork team_name x y",
    "   → create a new \"egg\" for a team at the given coordinates",
    "/incantate x y level",
    "   → simulate an incantation of the given level at the position",
    "/broadcast x y msg*",
    "   → simulate a broadcast from the given coordinates",
    "/set_logger_output filename",
    "   → change the output channel",
    "   →  OUT (1) / ERROR (2) / FILENAME (name of a file)",
    "/!\\ args* are optional"
};

typedef struct server_s server_t;
typedef struct client_s client_t;

int get_idx_ressources(char *ressource);

void get_help_debug(char *args, client_t *client, server_t *server);
// ! messages_commands.c
void list_clients(char *args, client_t *client, server_t *server);
void send_msg_ais(char *args, client_t *client, server_t *server);
void send_msg_guis(char *args, client_t *client, server_t *server);
// ! player_commands.c
void set_inventory(char *args, client_t *client, server_t *server);
void tp_player(char *args, client_t *client, server_t *server);
void kill_player(char *args, client_t *client, server_t *server);
void set_level(char *args, client_t *client, server_t *server);
// ! server_commands.c
void quit_server(char *args, client_t *client, server_t *server);
void clear_terminal(char *args, client_t *client, server_t *server);
void pause_world(char *args, client_t *client, server_t *server);
void play_world(char *args, client_t *client, server_t *server);
void restart_world(char *args, client_t *client, server_t *server);
// ! settings_commands.
void set_teams_slots(char *args, client_t *client, server_t *server);
void set_freq(char *args, client_t *client, server_t *server);
void set_refill(char *args, client_t *client, server_t *server);
void set_food(char *args, client_t *client, server_t *server);
// ! world_actions.c
void set_tile(char *args, client_t *client, server_t *server);
void clear_tile(char *args, client_t *client, server_t *server);
void simulate_fork(char *args, client_t *client, server_t *server);
void simulate_incantation(char *args, client_t *client, server_t *server);
void simulate_broadcast(char *args, client_t *client, server_t *server);

#endif /* !DEBUG_H_ */
