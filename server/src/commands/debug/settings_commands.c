/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** settings_commands
*/

#include "server.h"

void set_teams_slots(char *args, client_t *client, server_t *server)
{
    char *team_name = consume(args, " ");
    int quantity = GETTER(NULL);
    team_t *teams = server->world.teams;

    if (!team_name || quantity < 0) {
        write(client->fd, BAD, strlen(BAD));
        logger("settings_commands.c - set_teams_slots: bad args");
        return;
    }
    while (teams) {
        if (!strcmp(teams->name, team_name)) {
            write(client->fd, GOOD, strlen(GOOD));
            teams->slots = quantity;
            return;
        }
        teams = teams->next;
    }
    write(client->fd, BAD, strlen(BAD));
    logger("settings_commands.c - set_teams_slots: unknow team");
}

void set_freq(char *args, client_t *client, server_t *server)
{
    char *freq = consume(args, " ");
    int value = 0;

    if (!freq) {
        write(client->fd, BAD, strlen(BAD));
        logger("settings_commands.c - set_freq: bad args");
        return;
    }
    value = atoi(freq);
    if (value <= 0) {
        write(client->fd, BAD, strlen(BAD));
        logger("settings_commands.c - set_freq: bad freq");
        return;
    }
    server->world.freq = value;
    write(client->fd, GOOD, strlen(GOOD));
}

void set_refill(char *args, client_t *client, server_t *server)
{
    char *status = consume(args, " ");
    int boolean = string_to_bool(status);

    if (boolean == 2) {
        write(client->fd, BAD, strlen(BAD));
        logger("settings_commands.c - set_refill: bad args");
        return;
    }
    server->no_refills = boolean;
    write(client->fd, GOOD, strlen(GOOD));
}

void set_food(char *args, client_t *client, server_t *server)
{
    char *status = consume(args, " ");
    int boolean = string_to_bool(status);

    if (boolean == 2) {
        write(client->fd, BAD, strlen(BAD));
        logger("settings_commands.c - set_food: bad args");
        return;
    }
    server->no_foods = boolean;
    write(client->fd, GOOD, strlen(GOOD));
}
