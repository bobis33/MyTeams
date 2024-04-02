/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** server_client
*/

#include "server.h"

#include <netinet/in.h>
#include <unistd.h>
#include <uuid/uuid.h>

int accept_client(server_t *server)
{
    int clientSocket = accept(server->socket, NULL, NULL);

    if (clientSocket == -1)
        return ERROR;
    server->clients[clientSocket].socket = clientSocket;
    uuid_generate(server->clients[clientSocket].uuid);
    FD_SET(clientSocket, &server->readFds);
    return SUCCESS;
}

void kick_client(server_t *server, int clientSocket)
{
    close(clientSocket);
    server->clients[clientSocket].socket = 0;
    uuid_clear(server->clients[clientSocket].uuid);
    FD_CLR(clientSocket, &server->readFds);
}
