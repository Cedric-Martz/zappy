/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** world
*/

#ifndef WORLD_H_
    #define WORLD_H_

    #define RESSOURCES_NB 7
    #define COORD_IN_MAP(pos, width) pos.x + width * pos.y
    #define K_CONSTANT 30
    #define RADIUS 2
    #define BIG_BUFFER 65535

typedef struct vector_s {
    int x;
    int y;
}vector_t;

typedef struct info_s {
    vector_t *points;
    vector_t *active_list;
    int point_counter;
    int active_counter;
} info_t;

typedef struct egg_s {
    vector_t pos;
    char egg_id[MAX_ID];
    bool dead;
    struct egg_s *next;
} egg_t;

typedef struct team_s {
    char *name;
    size_t slots;
    size_t next_egg_id;
    egg_t *eggs;
    struct team_s *next;
} team_t;

typedef struct look_struct_s {
    vector_t pos;
    char line[BIG_BUFFER];
    int nb;
} look_struct_t;

typedef struct {
    // ? WIDTH/HEIGHT OF THE WORLD
    size_t width;
    size_t height;
    // ? TEAMS
    team_t *teams;
    // ? LIMITE OF CLIENTS FOR EACH TEAMS
    size_t clients_limit;
    // ? FREQUENCY OF UPDATE
    size_t freq;
    double refresh;
    info_t *refill_info;
    // ? MAP
    size_t **map;
    vector_t *randoms_coords;
    size_t idx;
    // ? PARSING
    bool need_to_stop;
} world_t;

static const char *const ressources[RESSOURCES_NB] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

static const double tiles_density[RESSOURCES_NB] = {
    0.5, // food
    0.3, // linemate
    0.15, // deraumere
    0.1, // sibur
    0.1, // mendiane
    0.08, // phiras
    0.05 // thystame
};

void init_world(server_t *server, size_t width, size_t height, bool reset);
void place_ressources(server_t *server);

#endif /* !WORLD_H_ */
