/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** ressources_actions
*/

#include "server.h"

void player_ressource_dropping(server_t *server, client_t *client, size_t idx)
{
    char buffer[MAX_BUFFER] = {0};

    snprintf(buffer, MAX_BUFFER, RESSOURCE_DROPPING, client->id, idx);
    for (client_t *curr = server->clients; curr; curr = curr->next)
        if (curr->type == GUI)
            write(curr->fd, buffer, strlen(buffer));
}

void player_ressource_collecting(server_t *server, client_t *client,
    size_t idx)
{
    char buffer[MAX_BUFFER] = {0};

    snprintf(buffer, MAX_BUFFER, RESSOURCE_COLLECTING, client->id, idx);
    for (client_t *curr = server->clients; curr; curr = curr->next)
        if (curr->type == GUI)
            write(curr->fd, buffer, strlen(buffer));
}
