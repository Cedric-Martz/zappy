/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** handle_flags
*/

#include "server.h"

bool check_flags(server_t *server)
{
    char error[57] = {0};
    const struct checks checks[CHECKS_NUMBER] = {
        {server->PORT <= 0, "bad PORT"},
        {WIDTH <= 0, "wrong width"},
        {HEIGHT <= 0, "wrong height"},
        {!server->world.teams, "there is no teams"},
        {server->world.clients_limit <= 0, "there is no client limite"},
        {server->world.freq <= 0, "bad frequency"},
        {server->world.need_to_stop, "two same teams"}
    };

    for (int i = 0; i < CHECKS_NUMBER; i++) {
        if (checks[i].condition) {
            strcpy(error, "handle_flags.c - check_flags: ");
            strcat(error, checks[i].error);
            logger(error);
            return false;
        }
    }
    return true;
}

void handle_flags(server_t *server, char **argv, bool *works)
{
    if (!argv || !(*argv))
        return;
    server->world.freq = 100;
    for (int j = 0; j < FLAGS_NUMBER; j++) {
        if (!strcmp(flags_tab[j].flags, (*argv))) {
            argv = flags_tab[j].function(server, argv + 1);
            handle_flags(server, argv, works);
            return;
        }
    }
    logger("handle_flags.c - handle_flags: unknow flag");
    *works = false;
    return;
}
