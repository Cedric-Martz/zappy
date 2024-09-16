/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** main
*/

#include "server.h"

void print_usage(void)
{
    const char *const help_tab[7] = {
        "USAGE: ./zappy_server -p port -x width -y height -n name1 "
        "name2 ... -c clientsNb -f freq\n",
        "      -p port: port number\n",
        "      -x width: width of the world\n",
        "      -y height: height of the world\n",
        "      -n name1 name2... : name of the team\n",
        "      -c clientsNb: number of authorized clients per team\n",
        "      -f freq: reciprocal of time unit for execution "
        "of actions\n"
    };

    for (int i = 0; i < 7; i++)
        write(1, help_tab[i], strlen(help_tab[i]));
}

bool check_args(int argc, char **argv)
{
    if (argc == 2) {
        if (!strcmp("-help", argv[0]) || !strcmp("-h", argv[0])) {
            print_usage();
            return false;
        }
        return true;
    }
    return true;
}

int main(int argc, char **argv)
{
    server_t *server = smalloc(sizeof(server_t), "main.c - main");

    memset(server, 0, sizeof(server_t));
    argv++;
    if (!check_args(argc, argv) || !setup_socket(server, argv)) {
        free_all(server);
        return 84;
    }
    if (!setup_server(server)) {
        free_all(server);
        return 84;
    }
    loop_server(server);
    free_all(server);
    return 0;
}
