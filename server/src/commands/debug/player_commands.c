/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** player_commands
*/

#include "server.h"

static void change_inventory(client_t *client, int idx, int quantity)
{
    for (int i = 0; i < RESSOURCES_NB; i++)
        if (i == idx || idx == RESSOURCES_NB)
            client->inventory[i] = quantity;
}

void set_inventory(char *args, client_t *client, server_t *server)
{
    int id = GETTER(args);
    int idx = get_idx_ressources(consume(NULL, " "));
    int quantity = GETTER(NULL);

    if (id < 0 || idx == -1 || quantity < 0) {
        write(client->fd, BAD, strlen(BAD));
        logger("player_commands.c - set_inventory: bad args");
        return;
    }
    for (client_t *curr = server->clients; curr; curr = curr->next) {
        if (curr->type != AI && curr->id != (size_t)id)
            continue;
        change_inventory(curr, idx, quantity);
        write(client->fd, GOOD, strlen(GOOD));
        return;
    }
    write(client->fd, BAD, strlen(BAD));
    logger("player_commands.c - set_inventory: unknow id");
}

void tp_player(char *args, client_t *client, server_t *server)
{
    int id = GETTER(args);
    vector_t vec = { GETTER(NULL), GETTER(NULL) };

    if (id < 0 || vec.x < 0 || vec.x >= (int)WIDTH ||
        vec.y < 0 || vec.y >= (int)HEIGHT) {
        write(client->fd, BAD, strlen(BAD));
        logger("player_commands.c - tp_player: bad args");
        return;
    }
    for (client_t *curr = server->clients; curr; curr = curr->next) {
        if (curr->id == (size_t)id) {
            curr->pos = vec;
            write(client->fd, GOOD, strlen(GOOD));
            return;
        }
    }
    write(client->fd, BAD, strlen(BAD));
    logger("player_commands.c - tp_player: unknow id");
}

void kill_player(char *args, client_t *client, server_t *server)
{
    int id = GETTER(args);

    if (id < 0) {
        write(client->fd, BAD, strlen(BAD));
        logger("player_commands.c - kill_player: bad args");
        return;
    }
    for (client_t *curr = server->clients; curr; curr = curr->next) {
        if (curr->id == (size_t)id) {
            curr->dead = true;
            write(client->fd, GOOD, strlen(GOOD));
            return;
        }
    }
    write(client->fd, BAD, strlen(BAD));
    logger("player_commands.c - kill_player: unknow id");
}

void set_level(char *args, client_t *client, server_t *server)
{
    int id = GETTER(args);
    int level = GETTER(NULL);

    if (id < 0 || level <= 0 || level > 8) {
        write(client->fd, BAD, strlen(BAD));
        logger("player_commands.c - set_level: bad args");
        return;
    }
    for (client_t *curr = server->clients; curr; curr = curr->next) {
        if (curr->type != AI || curr->id != (size_t)id)
            continue;
        curr->level = level;
        end_game(server, level);
        write(client->fd, GOOD, strlen(GOOD));
        return;
    }
    write(client->fd, BAD, strlen(BAD));
    logger("player_commands.c - set_level: unknow id");
}
