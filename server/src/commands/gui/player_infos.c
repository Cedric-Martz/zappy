/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** player_infos
*/

#include "server.h"

static int get_id(char *id, client_t *client)
{
    int value = 0;

    if (!id || id[0] != '#' || id[1] == '\0') {
        write(client->fd, BAD_COMMAND_GUI, strlen(BAD_COMMAND_GUI));
        logger("player_infos.c - get_player_position: bad args");
        return -1;
    }
    id++;
    value = atoi(id);
    if (value < 0) {
        write(client->fd, SYNTAX_ERROR_GUI, strlen(SYNTAX_ERROR_GUI));
        logger("player_infos.c - get_player_position: bad id");
    }
    return value;
}

void get_player_position(char *args, client_t *client, server_t *server)
{
    char *id = consume(args, " ");
    int value = 0;
    char buffer[MAX_BUFFER] = {0};

    value = get_id(id, client);
    if (value < 0)
        return;
    for (client_t *curr = server->clients; curr != NULL; curr = curr->next) {
        if (curr->type == AI && curr->id == (size_t)value) {
            snprintf(buffer, MAX_BUFFER, PLAYER_POSITION, curr->id,
            curr->pos.x, curr->pos.y, curr->direction);
            write(client->fd, buffer, strlen(buffer));
            return;
        }
    }
    logger("player_infos.c - get_player_position: unknow id");
    write(client->fd, BAD_COMMAND_GUI, strlen(BAD_COMMAND_GUI));
}

void get_player_level(char *args, client_t *client, server_t *server)
{
    char *id = consume(args, " ");
    int value = 0;
    char buffer[MAX_BUFFER] = {0};

    value = get_id(id, client);
    if (value < 0)
        return;
    for (client_t *curr = server->clients; curr != NULL; curr = curr->next) {
        if (curr->type == AI && curr->id == (size_t)value) {
            snprintf(buffer, MAX_BUFFER, PLAYER_LEVEL, curr->id, curr->level);
            write(client->fd, buffer, strlen(buffer));
            return;
        }
    }
    write(client->fd, BAD_COMMAND_GUI, strlen(BAD_COMMAND_GUI));
    logger("player_infos.c - get_player_level: unknow id");
}

void get_player_inventory(char *args, client_t *client, server_t *server)
{
    char *id = consume(args, " ");
    int value = 0;
    char buffer[MAX_BUFFER] = {0};

    value = get_id(id, client);
    if (value < 0)
        return;
    for (client_t *c = server->clients; c != NULL; c = c->next) {
        if (c->type == AI && c->id == (size_t)value) {
            snprintf(buffer, MAX_BUFFER, PLAYER_INVENTORY, c->id, c->pos.x,
            c->pos.y, c->inventory[0], c->inventory[1], c->inventory[2],
            c->inventory[3], c->inventory[4], c->inventory[5],
            c->inventory[6]);
            write(client->fd, buffer, strlen(buffer));
            return;
        }
    }
    write(client->fd, BAD_COMMAND_GUI, strlen(BAD_COMMAND_GUI));
    logger("player_infos.c - get_player_inventory: unknow id");
}

void player_death_gui(server_t *server, client_t *client)
{
    char buffer[MAX_BUFFER] = {0};

    snprintf(buffer, MAX_BUFFER, PLAYER_DEATH, client->id);
    for (client_t *curr = server->clients; curr; curr = curr->next) {
        if (curr->type == GUI)
            write(curr->fd, buffer, strlen(buffer));
    }
}
