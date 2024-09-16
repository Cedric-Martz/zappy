/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** execute_commands
*/

#include "server.h"

static void basic_command(client_t *client, server_t *server)
{
    if (!client->is_identified)
        choose_type(client->last_command, client, server);
    else
        handle_commands(client->last_command, client->args, client, server);
}

void execute_commands(client_t *client, server_t *server)
{
    if (!FD_ISSET(client->fd, &server->writefds))
            return;
    if (client->last_command[0] == '/')
        admin_commands(client, server);
    else
        basic_command(client, server);
    if (!server->clients)
        return;
    memset(client->last_command, 0, MAX_BUFFER);
    memset(client->args, 0, MAX_BUFFER);
    FD_CLR(client->fd, &server->writefds);
}
