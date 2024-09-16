/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** handle_server
*/

#include "server.h"

static void limit_command(client_t *client)
{
    int new_line = 0;
    int end = strlen(client->command) - 1;

    while (end >= 0) {
        new_line = count_char_number(client->command, '\n');
        if (new_line <= 10)
            return;
        client->command[end] = '\0';
        end--;
        while (end >= 0 && client->command[end] != '\n') {
            client->command[end] = '\0';
            end--;
        }
    }
}

void get_client_input(server_t *server)
{
    char buffer[MAX_BUFFER] = {0};
    int nb = 0;

    for (client_t *curr = server->clients; curr; curr = curr->next) {
        if (curr->fd <= 0 || !FD_ISSET(curr->fd, &server->readfds))
            continue;
        memset(buffer, 0, sizeof(char) * MAX_BUFFER);
        nb = read(curr->fd, &buffer, MAX_BUFFER - 1);
        if (nb <= 0) {
            curr->dead = true;
            return;
        }
        buffer[MAX_BUFFER - strlen(curr->command) - 1] = '\0';
        strcat(curr->command, buffer);
        if (curr->type == AI)
            limit_command(curr);
    }
    remove_client(server);
}

bool get_activity(server_t *server)
{
    int max_sd = server->serv_socket;
    int activity = 0;
    client_t *current = server->clients;
    struct timeval timeout = {0};

    timeout.tv_usec = 1;
    while (current) {
        if (current->fd <= 0) {
            current = current->next;
            continue;
        }
        FD_SET(current->fd, &server->readfds);
        if (current->fd > max_sd)
            max_sd = current->fd;
        current = current->next;
    }
    activity = select(max_sd + 1, &server->readfds,
    &server->writefds, NULL, &timeout);
    return (activity <= 0) ? false : true;
}

static bool add_new_client(server_t *server, int fd)
{
    client_t *current = server->clients;
    client_t *new = smalloc(sizeof(client_t),
        "handle_server.c - add_new_client");

    memset(new, 0, sizeof(client_t));
    new->fd = fd;
    if (!current) {
        server->clients = new;
        return true;
    }
    while (current->next)
        current = current->next;
    current->next = new;
    return true;
}

bool add_client(server_t *server)
{
    struct sockaddr *socket_adress = (struct sockaddr *)&server->adress;
    socklen_t *len = (socklen_t *)&server->len;

    if (!FD_ISSET(server->serv_socket, &server->readfds))
        return true;
    server->new_socket = accept(server->serv_socket, socket_adress, len);
    if (server->new_socket < 0)
        return false;
    if (!add_new_client(server, server->new_socket))
        return false;
    write(server->new_socket, CONNECTED, strlen(CONNECTED));
    return true;
}
