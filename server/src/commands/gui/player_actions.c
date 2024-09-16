/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** player_actions
*/

#include "server.h"

void player_expulsion(server_t *server, client_t *client)
{
    char buffer[MAX_BUFFER] = {0};

    snprintf(buffer, MAX_BUFFER, PLAYER_EXPULSION, client->id);
    for (client_t *curr = server->clients; curr != NULL; curr = curr->next)
        if (curr->type == GUI)
            write(curr->fd, buffer, strlen(buffer));
}

void player_broadcast(server_t *server, client_t *client, char *message)
{
    char buffer[MAX_BUFFER] = {0};

    snprintf(buffer, MAX_BUFFER, PLAYER_BROADCAST, client->id, message);
    for (client_t *curr = server->clients; curr != NULL; curr = curr->next)
        if (curr->type == GUI)
            write(curr->fd, buffer, strlen(buffer));
}

static void list_player(server_t *server, client_t *player,
    char buffer[MAX_BUFFER], int nb)
{
    int x = player->pos.x;
    int y = player->pos.y;
    size_t level = player->level;

    for (client_t *curr = server->clients; curr; curr = curr->next) {
        if (curr->pos.x != x || curr->pos.y != y || level != curr->level)
            continue;
        nb += snprintf(buffer + nb, MAX_BUFFER - nb, " #%ld", curr->id);
    }
    nb += snprintf(buffer + nb, MAX_BUFFER - nb, "\n");
}

void player_start_incantation(server_t *server, client_t *client)
{
    size_t x = client->pos.x;
    size_t y = client->pos.y;
    size_t level = client->level;
    char buffer[MAX_BUFFER] = {0};
    int nb = 0;

    nb += snprintf(buffer, MAX_BUFFER, START_INCANTATION, x, y, level);
    list_player(server, client, buffer, nb);
    for (client_t *curr = server->clients; curr; curr = curr->next)
        if (curr->type == GUI)
            write(curr->fd, buffer, strlen(buffer));
}

void player_end_incantation(server_t *server, client_t *client, bool result)
{
    size_t x = client->pos.x;
    size_t y = client->pos.y;
    char buffer[MAX_BUFFER] = {0};

    snprintf(buffer, MAX_BUFFER, END_INCANTATION, x, y, result);
    for (client_t *curr = server->clients; curr; curr = curr->next)
        if (curr->type == GUI)
            write(curr->fd, buffer, strlen(buffer));
}
