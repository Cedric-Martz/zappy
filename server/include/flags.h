/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** flags
*/

#ifndef FLAGS_H_
    #define FLAGS_H_

    #define FLAGS_NUMBER 6
    #define CHECKS_NUMBER 7

typedef struct server_s server_t;
typedef struct client_s client_t;

void handle_flags(server_t *server, char **argv, bool *works);
char **get_port(server_t *server, char **argv);
char **get_width(server_t *server, char **argv);
char **get_height(server_t *server, char **argv);
char **get_team_name(server_t *server, char **argv);
char **get_clients_limit(server_t *server, char **argv);
char **get_freq(server_t *server, char **argv);

struct flags {
    const char *flags;
    char **(*function)(server_t *server, char **argv);
};

static const struct flags flags_tab[FLAGS_NUMBER] = {
    { "-p", get_port }, { "-x", get_width },
    { "-y", get_height }, { "-n", get_team_name },
    { "-c", get_clients_limit }, { "-f", get_freq },
};

bool check_flags(server_t *server);

struct checks {
    const bool condition;
    const char *error;
};

#endif /* !FLAGS_H_ */
