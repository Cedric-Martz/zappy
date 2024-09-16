/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** setup_server
*/

#include "server.h"

bool setup_opt(server_t *server)
{
    int socket = server->serv_socket;
    int *opt = &server->opt;
    int set = setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, opt, sizeof(int));

    if (set < 0) {
        logger("setup_server.c - setup_opt: failed to set the socket options");
        return false;
    }
    return true;
}

bool setup_socket(server_t *server, char **argv)
{
    bool works = true;

    server->opt = 1;
    server->len = sizeof(server->adress);
    handle_flags(server, argv, &works);
    if (!works || !check_flags(server))
        return false;
    init_world(server, WIDTH, HEIGHT, false);
    server->serv_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->serv_socket == -1) {
        logger("setup_server.c - setup_socket: failed to create the socket");
        return false;
    }
    return setup_opt(server);
}

bool setup_server(server_t *server)
{
    int tmp = 0;

    memset(&server->adress, 0, sizeof(struct sockaddr_in));
    server->adress.sin_family = AF_INET;
    server->adress.sin_port = htons(server->PORT);
    server->adress.sin_addr.s_addr = INADDR_ANY;
    tmp = bind(server->serv_socket, (struct sockaddr*) &server->adress,
        server->len);
    if (tmp < 0) {
        logger("setup_server.c - setup_server: failed to bind the socket");
        return false;
    }
    if (listen(server->serv_socket, BACKLOG) < 0) {
        logger("setup_server.c - setup_server: failed to listen the socket");
        return false;
    }
    server->clients = NULL;
    return true;
}
