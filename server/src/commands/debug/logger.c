/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** logger
*/

#include "server.h"

void set_file_output(char *args, client_t *client, server_t *server)
{
    char *filename = consume(args, " ");

    (void)client;
    (void)server;
    if (!filename) {
        logger("logger.c - set_file_output: need to give a filename");
        return;
    }
    output_logger(filename, SET);
    write(client->fd, GOOD, strlen(GOOD));
}

static int set_logger_channel(char *filename)
{
    int new_fd = 0;

    if (!strcmp(filename, "ERROR"))
        return 2;
    if (!strcmp(filename, "OUT"))
        return 1;
    new_fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (new_fd == -1)
        logger("logger.c set_logger_channel: Failed to change output\n");
    return new_fd;
}

int output_logger(char *filename, enum action_logger action)
{
    static int fd = 2;
    int save = 0;

    if (action == GET)
        return fd;
    if (action == SET) {
        save = set_logger_channel(filename);
        if (save == -1)
            return 0;
        if (fd > 2)
            close(fd);
        fd = save;
    }
    return 0;
}

void logger(const char *message)
{
    time_t current_time;
    struct tm *local_time = NULL;
    char formatted_time[20];
    int fd = output_logger(NULL, GET);
    char buffer[MAX_BUFFER] = {0};

    time(&current_time);
    local_time = localtime(&current_time);
    strftime(formatted_time, sizeof(formatted_time),
        "%d/%m/%y - %H:%M:%S", local_time);
    snprintf(buffer, MAX_BUFFER, "[%s]: %s\n", formatted_time, message);
    write(fd, buffer, strlen(buffer));
}
