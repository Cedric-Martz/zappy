/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** loop_server
*/

#include "server.h"

bool handle_signal(bool getter, bool stat)
{
    static bool loop_enable = false;

    if (!getter)
        loop_enable = stat;
    return loop_enable;
}

void signal_handler(int signum)
{
    (void)signum;
    handle_signal(false, false);
}

static void get_one_command(client_t *client, server_t *server)
{
    if (!count_char_number(client->command, '\n'))
        return;
    if (client->command[0])
        handle_one_command(client, server);
}

static void check_gui_commands_next(client_t *client, server_t *server,
    char *command)
{
    char *rest = consume(NULL, "");
    char tmp[MAX_BUFFER] = {0};

    if (rest)
        strcpy(tmp, rest);
    handle_buffer_management(command, client, server);
    execute_commands(client, server);
    memset(client->command, 0, MAX_BUFFER);
    strcpy(client->command, tmp);
}

static void check_gui_commands(client_t *client, server_t *server)
{
    char *command = NULL;

    if (client->mctOn) {
        get_tiles_info(client, server);
        return;
    }
    if (!client->command[0])
        return;
    while (count_char_number(client->command, '\n')) {
        if (client->mctOn)
            break;
        if (!client->command[0])
            break;
        command = consume(client->command, "\r\n");
        if (!command)
            break;
        check_gui_commands_next(client, server, command);
    }
}

static void check_ai_commands(client_t *client, server_t *server)
{
    if (client->wait)
        return;
    if (client->last_command[0]) {
        execute_commands(client, server);
        return;
    }
    if (!client->wait && client->incantation)
        check_incantation(client, server);
    get_one_command(client, server);
}

void check_if_commands(server_t *server)
{
    for (client_t *curr = server->clients; curr; curr = curr->next) {
        if (curr->type == AI)
            check_ai_commands(curr, server);
        else
            check_gui_commands(curr, server);
    }
    remove_client(server);
}

void loop_server(server_t *server)
{
    handle_signal(false, true);
    signal(SIGINT, signal_handler);
    gettimeofday(&server->prev_time, NULL);
    while (handle_signal(true, true)) {
        check_if_commands(server);
        update_time(server);
        FD_ZERO(&server->readfds);
        FD_SET(server->serv_socket, &server->readfds);
        if (!get_activity(server))
            continue;
        if (!add_client(server))
            break;
        get_client_input(server);
    }
    signal(SIGINT, SIG_DFL);
}
