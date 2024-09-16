/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** get_team_name
*/

#include "server.h"
#include <string.h>

void add_one_team(server_t *server, char *name)
{
    team_t *tmp = server->world.teams;
    team_t *new = smalloc(sizeof(team_t), "get_team_name.c - add_one_team");

    memset(new, 0, sizeof(team_t));
    new->name = strdup(name);
    if (!server->world.teams)
        server->world.teams = new;
    else {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

void check_team(char *first, char *second, server_t *server)
{
    if (!strcmp(first, second))
        server->world.need_to_stop = true;
}

char **get_team_name(server_t *server, char **argv)
{
    while (argv[0] && argv[0][0] != '-') {
        add_one_team(server, argv[0]);
        argv++;
    }
    for (team_t *curr = server->world.teams; curr; curr = curr->next) {
        for (team_t *next = curr->next; next; next = next->next) {
            check_team(curr->name, next->name, server);
        }
        if (server->world.need_to_stop)
            break;
    }
    return argv;
}
