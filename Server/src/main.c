/*
** EPITECH PROJECT, 2024
** myteams | server
** File description:
** main.c
*/

#include "server.h"

int main(int argc, const char *argv[])
{
    server_t server = {0};

    (void) argc;
    (void) argv;
    if (!init_server(&server, 8080))
        return EXIT_ERROR;
    shutdown_server(&server);
    return SUCCESS;
}
