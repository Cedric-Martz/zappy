/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** help
*/

#include "server.h"

void get_help_ai(char *args, client_t *client, server_t *server)
{
    char buffer[MAX_BUFFER] = {0};
    int nb = 0;

    (void)args;
    (void)server;
    for (int i = 0; i < COMMANDS_AI - 1; i++)
        nb += snprintf(buffer + nb, MAX_BUFFER - nb, "#%s\n",
            command_info_ia[i]);
    write(client->fd, buffer, nb);
}

void get_help_gui(char *args, client_t *client, server_t *server)
{
    char buffer[MAX_BUFFER] = {0};
    int nb = 0;

    (void)args;
    (void)server;
    for (int i = 0; i < COMMANDS_GUI - 1; i++)
        nb += snprintf(buffer + nb, MAX_BUFFER - nb, "#%s\n",
            command_info_gui[i]);
    write(client->fd, buffer, nb);
}

void get_help_debug(char *args, client_t *client, server_t *server)
{
    char buffer[MAX_BUFFER] = {0};
    int nb = 0;

    (void)args;
    (void)server;
    for (int i = 0; i < HELP_TAB_DEBUG; i++)
        nb += snprintf(buffer + nb, MAX_BUFFER - nb, "#%s\n",
            command_info_debug[i]);
    write(client->fd, buffer, nb);
}

void get_help_default(client_t *client, server_t *server)
{
    (void)server;
    write(client->fd, HELP, strlen(HELP));
}
