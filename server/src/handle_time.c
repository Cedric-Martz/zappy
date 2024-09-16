/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** handle_time
*/

#include "server.h"

static double get_elapsed_time(struct timeval *curr, struct timeval *prev,
    size_t coef)
{
    long seconds;
    long useconds;
    double elapsed;

    if (gettimeofday(curr, NULL) == -1) {
        logger("handle_time.c - get_elapsed_time - gettimeofday error");
        return -1.0;
    }
    seconds = curr->tv_sec - prev->tv_sec;
    useconds = curr->tv_usec - prev->tv_usec;
    elapsed = seconds + useconds / 1000000.0;
    *prev = *curr;
    return elapsed * coef;
}

static void check_refills(server_t *server, double elapsed)
{
    if (!server->no_refills) {
        server->world.refresh -= elapsed;
        if (server->world.refresh < 0)
            place_ressources(server);
    }
}

static void check_eat_player(server_t *server, client_t *client,
    double elapsed)
{
    if (server->no_foods || client->type != AI)
        return;
    client->eat = (client->eat - elapsed < 0.0) ? 0.0 :
    client->eat - elapsed;
    if (client->eat == 0.0) {
        if (!client->inventory[0]) {
            player_death_ai(server, client);
            client->dead = true;
            return;
        }
        client->inventory[0]--;
        client->eat = 126.0;
    }
}

void update_time(server_t *server)
{
    double elapsed = get_elapsed_time(&server->curr_time, &server->prev_time,
        server->world.freq);

    if (elapsed == -1.0)
        return;
    if (server->stop)
        return;
    for (client_t *curr = server->clients; curr; curr = curr->next) {
        if (curr->fd <= 0)
            continue;
        curr->wait = (curr->wait - elapsed < 0.0) ? 0.0 : curr->wait - elapsed;
        check_eat_player(server, curr, elapsed);
    }
    remove_client(server);
    check_refills(server, elapsed);
}
