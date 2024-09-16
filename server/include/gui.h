/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** gui
*/

#ifndef GUI_H_
    #define GUI_H_

    #define COMMANDS_GUI 10
    #define MAX_ID 1048

static const char *const command_info_gui[COMMANDS_GUI - 1] = {
    "msz (map size)",
    "bct (content of a tile)",
    "mct (tiles content of the map)",
    "tna (name of all the teams)",
    "ppo (show player's position)",
    "plv (show player's level)",
    "pin (show player's inventory)",
    "sgt (show time unit)",
    "sst (time unit modification)"
};

typedef struct server_s server_t;
typedef struct client_s client_t;

// ! COMMANDS
void get_help_gui(char *args, client_t *client, server_t *server);
void get_map_size(char *args, client_t *client, server_t *server);
void get_tile_info(char *args, client_t *client, server_t *server);
void get_tiles_info(client_t *client, server_t *server);
void trigger_mct(char *args, client_t *client, server_t *server);
void get_all_teams(char *args, client_t *client, server_t *server);
void get_player_position(char *args, client_t *client, server_t *server);
void get_player_level(char *args, client_t *client, server_t *server);
void get_player_inventory(char *args, client_t *client, server_t *server);
void time_request(char *args, client_t *client, server_t *server);
void time_change(char *args, client_t *client, server_t *server);
// ! ACTIONS
void player_expulsion(server_t *server, client_t *client);
void player_broadcast(server_t *server, client_t *client, char *message);
void player_start_incantation(server_t *server, client_t *client);
void player_end_incantation(server_t *server, client_t *client, bool result);
void player_egg_laying(server_t *server, client_t *client);
void player_ressource_dropping(server_t *server, client_t *client, size_t idx);
void player_ressource_collecting(server_t *server, client_t *client,
    size_t idx);
void player_death_gui(server_t *server, client_t *client);
void egg_laid(server_t *server, client_t *client, char egg_id[MAX_ID]);
void egg_connection(server_t *server, client_t *client, char egg_id[MAX_ID]);
void egg_death(server_t *server, char egg_id[MAX_ID]);
void end_game(server_t *server, size_t level);
void server_message(server_t *server, char *message);

#endif /* !GUI_H_ */
