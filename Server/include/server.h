/*
** EPITECH PROJECT, 2024
** myftp | server
** File description:
** server.h
*/

#pragma once

#include <sys/select.h>
#include <stdbool.h>

#define SUCCESS 0
#define ERROR -1
#define EXIT_ERROR 84

typedef struct client_s {
    char *ip;
    int port;
    int socket;
} client_t;

typedef struct server_s {
    int socket;
    bool shouldStop;
    client_t clients[FD_SETSIZE];
    fd_set readFds;
} server_t;

bool init_server(server_t *server, int port);

void shutdown_server(server_t *server);
