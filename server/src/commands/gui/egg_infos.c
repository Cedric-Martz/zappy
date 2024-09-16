/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** egg_infos
*/

#include "server.h"

void player_egg_laying(server_t *server, client_t *client)
{
    char buffer[MAX_BUFFER] = {0};

    snprintf(buffer, MAX_BUFFER, PLAYER_EGG_LAYING, client->id);
    for (client_t *curr = server->clients; curr; curr = curr->next)
        if (curr->type == GUI)
            write(curr->fd, buffer, strlen(buffer));
}

void egg_laid(server_t *server, client_t *client, char egg_id[MAX_ID])
{
    char buffer[MAX_BUFFER] = {0};

    snprintf(buffer, MAX_BUFFER, EGG_LAID, egg_id, client->id,
        client->pos.x, client->pos.y);
    for (client_t *curr = server->clients; curr != NULL; curr = curr->next)
        if (curr->type == GUI)
            write(curr->fd, buffer, strlen(buffer));
}

void egg_connection(server_t *server, client_t *client, char egg_id[MAX_ID])
{
    char buffer[MAX_BUFFER] = {0};
    int nb = 0;

    nb += snprintf(buffer + nb, MAX_BUFFER - nb, EGG_CONNECTION, egg_id);
    nb += snprintf(buffer + nb, MAX_BUFFER - nb, NEW_PLAYER, client->id,
        client->pos.x, client->pos.y, client->direction, client->level,
        client->team);
    for (client_t *curr = server->clients; curr; curr = curr->next)
        if (curr->type == GUI)
            write(curr->fd, buffer, strlen(buffer));
}

void egg_death(server_t *server, char egg_id[MAX_ID])
{
    char buffer[MAX_BUFFER] = {0};

    snprintf(buffer, MAX_BUFFER, EGG_DEATH, egg_id);
    for (client_t *curr = server->clients; curr; curr = curr->next)
        if (curr->type == GUI)
            write(curr->fd, buffer, strlen(buffer));
}
