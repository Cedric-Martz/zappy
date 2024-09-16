/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** get_clients_limit
*/

#include "server.h"

char **get_port(server_t *server, char **argv)
{
    server->PORT = atoi(*argv);
    return argv + 1;
}

char **get_width(server_t *server, char **argv)
{
    WIDTH = atoi(*argv);
    return argv + 1;
}

char **get_height(server_t *server, char **argv)
{
    HEIGHT = atoi(*argv);
    return argv + 1;
}

char **get_clients_limit(server_t *server, char **argv)
{
    server->world.clients_limit = atoi(*argv);
    return argv + 1;
}

char **get_freq(server_t *server, char **argv)
{
    server->world.freq = atoi(*argv);
    return argv + 1;
}
