/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** ai
*/

#ifndef AI_H_
    #define AI_H_

    #define _PI 3.14159265358979323846
    #define COMMANDS_AI 13
    #define LEVELUP_MAX 7

struct delay {
    const char *command;
    int value;
};

static const struct delay delay_tab[COMMANDS_AI - 1] = {
    { "Forward", 7.0},
    { "Right", 7.0},
    { "Left", 7.0},
    { "Look", 7.0},
    { "Inventory", 1.0},
    { "Broadcast", 7.0},
    { "Connect_nbr", 0.0},
    { "Fork", 42.0},
    { "Eject", 7.0},
    { "Take", 7.0},
    { "Set", 7.0},
    { "Incantation", 0.0},
};

static const char *const command_info_ia[COMMANDS_AI - 1] = {
    "Forward      move up one tile",
    "Right        turn 90° right",
    "Left         turn 90° left",
    "Look         look around",
    "Inventory    show inventory",
    "Broadcast    send broadcast",
    "Connect_nbr  number of team unused slots",
    "Fork         fork a player",
    "Eject        eject players from this tile",
    "Take         take object",
    "Set          drop object",
    "Incantation  start incantation (level up)"
};

typedef struct server_s server_t;
typedef struct client_s client_t;

// ! COMMANDS
void get_help_ai(char *args, client_t *client, server_t *server);
void go_forward(char *args, client_t *client, server_t *server);
void go_right(char *args, client_t *client, server_t *server);
void go_left(char *args, client_t *client, server_t *server);
void look_around(char *args, client_t *client, server_t *server);
void show_inventory(char *args, client_t *client, server_t *server);
void send_broadcast(char *args, client_t *client, server_t *server);
void show_unused_slots(char *args, client_t *client, server_t *server);
void fork_player(char *args, client_t *client, server_t *server);
void eject_player(char *args, client_t *client, server_t *server);
void take_object(char *args, client_t *client, server_t *server);
void drop_object(char *args, client_t *client, server_t *server);
void start_incancation(char *args, client_t *client, server_t *server);
// ! ACTIONS
void player_death_ai(server_t *server, client_t *client);
void check_incantation(client_t *client, server_t *server);

enum orientation_type {
    Undefined = 0,
    N,
    E,
    S,
    W
};

struct moves {
    enum orientation_type direction;
    int x;
    int y;
};

static const struct moves forward[4] = {
    {N, 0, -1},
    {S, 0, 1},
    {E, 1, 0},
    {W, -1, 0}
};

struct turn {
    enum orientation_type left;
    enum orientation_type right;
};

static const struct turn turns[4] = {
    {N, E},
    {S, W},
    {E, S},
    {W, N}
};

static const size_t levelup_condition[LEVELUP_MAX][7] = {
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1}
};

static const float tab_angle[8][2] = {
    {337.5, 22.5},
    {292.5, 337.5},
    {247.5, 292.5},
    {202.5, 247.5},
    {157.5, 202.5},
    {112.5, 157.5},
    {67.5, 112.5},
    {22.5, 67.5}
};

#endif /* !IA_H_ */
