/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** server_client
*/

#include "server.h"

#include <netinet/in.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

int accept_client(server_t *server)
{
    int clientSocket = accept(server->socket, NULL, NULL);

    if (clientSocket == -1)
        return ERROR;
    server->clients[clientSocket].socket = clientSocket;
    server->clients[clientSocket].user = NULL;
    FD_SET(clientSocket, &server->readFds);
    return SUCCESS;
}

void kick_client(server_t *server, int clientSocket)
{
    close(clientSocket);
    server->clients[clientSocket].socket = 0;
    FD_CLR(clientSocket, &server->readFds);
}

void send_to_client(server_t *server, int clientSocket, char *message, ...)
{
    fd_set writefds;
    struct timeval timeVal = { .tv_sec = 0, .tv_usec = 500 };
    va_list args;

    FD_ZERO(&writefds);
    FD_SET(clientSocket, &writefds);
    if (select(clientSocket + 1, NULL, &writefds, NULL, &timeVal) == -1)
        kick_client(server, clientSocket);
    else {
        va_start(args, message);
        vdprintf(clientSocket, message, args);
    }
}
