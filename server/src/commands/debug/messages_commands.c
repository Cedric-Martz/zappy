/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** messages_commands
*/

#include "server.h"

static void show_inventory_player(client_t *curr, char buffer[MAX_BUFFER],
    int *nb)
{
    int tmp = (*nb);

    tmp += snprintf(buffer + tmp, MAX_BUFFER - tmp, "#id [%ld]\n", curr->id);
    tmp += snprintf(buffer + tmp, MAX_BUFFER - tmp, "#pos [%d][%d]\n",
        curr->pos.x, curr->pos.y);
    tmp += snprintf(buffer + tmp, MAX_BUFFER - tmp, "#level [%ld]\n",
        curr->level);
    tmp += snprintf(buffer + tmp, MAX_BUFFER - tmp, "#[");
    for (int i = 0; i < RESSOURCES_NB; i++) {
        if (i)
            tmp += snprintf(buffer + tmp, MAX_BUFFER - tmp, ", ");
        tmp += snprintf(buffer + tmp, MAX_BUFFER - tmp,
            "%s %ld", ressources[i], curr->inventory[i]);
    }
    tmp += snprintf(buffer + tmp, MAX_BUFFER - tmp, "]\n");
    (*nb) = tmp;
}

void list_clients(char *args, client_t *client, server_t *server)
{
    char *id = consume(args, " ");
    char buffer[MAX_BUFFER] = {0};
    int nb = 0;

    for (client_t *curr = server->clients; curr; curr = curr->next) {
        if (curr->type != AI)
            continue;
        if (id && atoi(id) != (int)curr->id)
            continue;
        show_inventory_player(curr, buffer, &nb);
    }
    if (!nb) {
        write(client->fd, BAD, strlen(BAD));
        logger("messages_commands.c - list_clients: unknow id");
        return;
    }
    write(client->fd, buffer, strlen(buffer));
}

void send_msg_ais(char *args, client_t *client, server_t *server)
{
    char *message = args ? args : "";
    char buffer[BIG_BUFFER] = {0};

    (void)client;
    snprintf(buffer, BIG_BUFFER, "#%s\n", message);
    for (client_t *curr = server->clients; curr; curr = curr->next)
        if (curr->type == AI)
            write(curr->fd, buffer, strlen(buffer));
}

void send_msg_guis(char *args, client_t *client, server_t *server)
{
    char *message = args ? args : "";

    (void)client;
    server_message(server, message);
}
