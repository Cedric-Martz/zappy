/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** handle_commands
*/

#include "server.h"

static void handle_delay(client_t *client)
{
    for (int i = 0; i < COMMANDS_AI - 1; i++) {
        if (!strcmp(client->last_command, delay_tab[i].command)) {
            client->wait = delay_tab[i].value;
            return;
        }
    }
}

void handle_buffer_management(char *buffer, client_t *client,
    server_t *server)
{
    char *command = strtok(buffer, " \t");
    char *args = strtok(NULL, "");

    if (!command)
        return;
    strcpy(client->last_command, command);
    if (args)
        strcpy(client->args, args);
    FD_SET(client->fd, &server->writefds);
    if (client->type == AI)
        handle_delay(client);
}

void handle_one_command(client_t *client, server_t *server)
{
    char *tmp = strdup(client->command);
    char *rest = strdup(strchr(tmp, '\n') + 1);
    char *command = consume(tmp, "\r\n");

    memset(client->command, 0, MAX_BUFFER);
    if (!command) {
        if (rest)
            free(rest);
        return free(tmp);
    }
    handle_buffer_management(command, client, server);
    if (rest) {
        if (rest[0] != '\0')
            strcpy(client->command, rest);
        free(rest);
    }
    free(tmp);
}

void handle_commands(char *command, char *substring,
    client_t *client, server_t *server)
{
    for (int i = 0; i < COMMANDS_NUMBER; i++) {
        if (strcmp(commands_tab[i].command, command))
            continue;
        if (client->type == commands_tab[i].type)
            return commands_tab[i].function(substring, client, server);
    }
    if (client->type == GUI) {
        write(client->fd, BAD_COMMAND_GUI, strlen(BAD_COMMAND_GUI));
        logger("handle_commands.c - handle_commands: bad command GUI");
    } else {
        write(client->fd, BAD, strlen(BAD));
        logger("handle_commands.c - handle_commands: bad command AI");
    }
}
