/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** time_infos
*/

#include "server.h"

void time_request(char *args, client_t *client, server_t *server)
{
    char buffer[MAX_BUFFER] = {0};

    (void)args;
    snprintf(buffer, MAX_BUFFER, TIME_REQUEST, server->world.freq);
    write(client->fd, buffer, strlen(buffer));
}

void time_change(char *args, client_t *client, server_t *server)
{
    char *time_arg = consume(args, "");
    int time = 0;
    char buffer[MAX_BUFFER] = {0};

    if (!time_arg) {
        write(client->fd, BAD_COMMAND_GUI, strlen(BAD_COMMAND_GUI));
        return logger("time_infos.c - time_change: bad args");
    }
    time = atoi(time_arg);
    if (time < 1) {
        write(client->fd, SYNTAX_ERROR_GUI, strlen(SYNTAX_ERROR_GUI));
        return logger("time_infos.c - time_change: bad freq");
    }
    server->world.freq = (size_t)time;
    snprintf(buffer, MAX_BUFFER, TIME_CHANGE, server->world.freq);
    write(client->fd, buffer, strlen(buffer));
}

static void complete_tab(server_t *server, team_t *team, int *tab_team)
{
    for (client_t *curr = server->clients; curr != NULL; curr = curr->next) {
        if (curr->type != AI || curr->level < 8)
            continue;
        if (strcmp(curr->team, team->name) == 0)
            (*tab_team)++;
    }
}

static char *find_max_level_8(int *tab_team, int nb_team, server_t *server)
{
    int max = 0;
    team_t *team = server->world.teams;
    char *team_name = NULL;

    for (int i = 0; i < nb_team; i++) {
        if (max >= tab_team[i]) {
            team = team->next;
            continue;
        }
        max = tab_team[i];
        if (team_name)
            free(team_name);
        team_name = strdup(team->name);
        team = team->next;
    }
    if (max >= 6)
        return team_name;
    if (team_name)
        free(team_name);
    return NULL;
}

static char *check_win_team(server_t *server, int nb_team)
{
    int *tab_team = smalloc(sizeof(int) * nb_team,
        "time_infos.c - check_win_team");
    char *team_name = NULL;
    int i = 0;

    memset(tab_team, 0, sizeof(int) * nb_team);
    for (team_t *team = server->world.teams; team != NULL; team = team->next) {
        complete_tab(server, team, &tab_team[i]);
        i++;
    }
    team_name = find_max_level_8(tab_team, nb_team, server);
    free(tab_team);
    return team_name;
}

static char *get_win_team(server_t *server, size_t level)
{
    int nb_team = 0;

    if (level != 8)
        return NULL;
    for (team_t *team = server->world.teams; team != NULL; team = team->next)
        nb_team++;
    return check_win_team(server, nb_team);
}

void end_game(server_t *server, size_t level)
{
    char *team_name = get_win_team(server, level);
    char buffer[MAX_BUFFER] = {0};
    int nb = 0;

    if (team_name == NULL)
        return;
    nb += snprintf(buffer, MAX_BUFFER, END_GAME, team_name);
    for (client_t *curr = server->clients; curr != NULL; curr = curr->next) {
        if (curr->type == AI && curr->level == 8)
            nb += snprintf(buffer + nb, MAX_BUFFER - nb, PLAYER_LEVEL,
                curr->id, curr->level);
    }
    for (client_t *curr = server->clients; curr != NULL; curr = curr->next) {
        if (curr->type == GUI)
            write(curr->fd, buffer, strlen(buffer));
        if (curr->type == AI)
            curr->dead = true;
    }
    server->end_game = true;
    free(team_name);
}

void server_message(server_t *server, char *message)
{
    char buffer[BIG_BUFFER] = {0};

    snprintf(buffer, BIG_BUFFER, SERVER_MESSAGE, message);
    for (client_t *curr = server->clients; curr != NULL; curr = curr->next){
        if (curr->type != GUI)
            continue;
        write(curr->fd, buffer, strlen(buffer));
    }
}
