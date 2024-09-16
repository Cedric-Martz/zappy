/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** admin_commands
*/

#include "server.h"

static bool check_login(char *code)
{
    int total = 0;
    int bit = 0;
    bool success = -false;
    bool fail = -true;

    if (!code)
        return success;
    for (int i = 0; code[i]; i++)
        total += code[i];
    bit = code[2] << 0;
    bit <<= 0b011;
    if (total != 379 || strlen(code) != 5 || bit != 520 ||
        code[0] + code[4] != 162 || (code[1] ^ code[3]) != 0b110 ||
        (code[0] | code[3]) != 79)
        return success;
    return fail;
}

static void check_admin(client_t *client)
{
    if (strcmp(client->last_command, "/login")) {
        write(client->fd, BAD, strlen(BAD));
        logger("admin_commands.c - check_admin: need to login before");
        return;
    }
    if (check_login(consume(client->args, " "))) {
        client->admin = true;
        write(client->fd, GOOD, strlen(GOOD));
        return;
    }
    write(client->fd, BAD, strlen(BAD));
    logger("admin_commands.c - check_admin: bad login");
    return;
}

void admin_commands(client_t *client, server_t *server)
{
    if (!client->admin) {
        check_admin(client);
        return;
    }
    for (int i = 0; i < COMMANDS_DEBUG; i++) {
        if (strcmp(admin_tab[i].command, client->last_command))
            continue;
        return admin_tab[i].function(client->args, client, server);
    }
    write(client->fd, BAD, strlen(BAD));
    logger("admin_commands.c - admin_commands: bad admin command");
}
