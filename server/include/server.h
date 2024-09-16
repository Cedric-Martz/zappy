/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include <string.h>
    #include <stdio.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <sys/select.h>
    #include <stdbool.h>
    #include <sys/wait.h>
    #include <signal.h>
    #include <sys/stat.h>
    #include <dirent.h>
    #include <fcntl.h>
    #include <time.h>
    #include <sys/time.h>
    #include <math.h>
    #include <errno.h>

    #include "messages.h"
    #include "commands.h"
    #include "world.h"
    #include "flags.h"

    #define BACKLOG 5
    #define MAX_BUFFER 4096
    #define MAX_CLIENTS 50
    #define CLEAR "\033[2J\033[1;1H"
    #define WIDTH server->world.width
    #define HEIGHT server->world.height

typedef struct client_s {
    // ? CLIENT INFO
    int fd;
    bool is_identified;
    // ? BUFFER MANAGEMENT
    char command[MAX_BUFFER];
    char last_command[MAX_BUFFER];
    char args[MAX_BUFFER];
    // ? CLIENT LIST
    struct client_s *next;
    // ? PLAYER INFO
    enum client_type type;
    char team[128];
    // ? IA
    size_t id;
    vector_t pos;
    size_t level;
    bool incantation;
    enum orientation_type direction;
    size_t inventory[7];
    // ? TIME HANDLE
    double wait;
    double eat;
    // ? DEAD
    bool dead;
    // ? ADMIN PERMS
    bool admin;
    // ? GUI OPTI
    bool mctOn;
    char map[BIG_BUFFER];
    int nb;
} client_t;

typedef struct server_s {
    // ? SERVER INFORMATIONS
    int PORT;
    int serv_socket;
    struct sockaddr_in adress;
    int len;
    int opt;
    world_t world;
    bool end_game;
    // ? CLIENTS INFORMATIONS
    int new_socket;
    client_t *clients;
    fd_set readfds;
    fd_set writefds;
    // ? TIME HANDLE
    struct timeval curr_time;
    struct timeval prev_time;
    // ? DEBUG MODE
    bool stop;
    bool no_refills;
    bool no_foods;
} server_t;

bool setup_socket(server_t *server, char **argv);
bool setup_server(server_t *server);

bool handle_signal(bool getter, bool stat);
void loop_server(server_t *server);

bool get_activity(server_t *server);
void get_client_input(server_t *server);
bool add_client(server_t *server);
void update_time(server_t *server);

void free_eggs(team_t *team, bool erase_team);
void free_clients(client_t *clients);
void remove_client(server_t *server);
void free_all(server_t *server);

// ? UTILS
// ! calcul_utils.c
int get_value(char *string);
int compute_sound(vector_t sender, vector_t receiver, int direction);
bool check_levelup_condition(vector_t pos, size_t level, server_t *server);
// ! string_utils.c
void *smalloc(size_t size, char *func);
int string_to_bool(char *string);
int count_char_number(char *str, char c);
char *consume(char *str, char *rejected);
// ! tab_utils.c
int tab_len(char **tab);
int last_occurence_of(char c, char *str);
int count_my_words(char *str, char *reject);
char **split_my_args(char *str, char *rejected);
void free_tab(char **tab);

    #define GETTER(args) get_value(consume(args, " "))

#endif /* !SERVER_H_ */
