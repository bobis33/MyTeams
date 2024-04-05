/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** user_commands
*/

#include "commands.h"
#include "server.h"

#include <stdio.h>
#include <string.h>
#include <sys/select.h>

static bool is_user_connected(server_t *server, uuid_t user_uuid)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->clients[i].user != NULL &&
            uuid_compare(server->clients[i].user->uuid, user_uuid) == 0) {
            return true;
        }
    }
    return false;
}

void handle_users_command(server_t *server, int clientSocket, char *command)
{
    char buffer[1024] = {0};
    int offset = 0;
    char uuidStr[37];

    if (strncmp(command, "/users\r\n", 8) != 0) {
        send_to_client(server, clientSocket, "500: invalid syntax\n");
        return;
    }
    if (server->clients[clientSocket].user == NULL) {
        send_to_client(server, clientSocket, "502: not logged in\n");
        return;
    }
    offset += sprintf(buffer, "102: user list [");
    for (int i = 0; i < server->usersCount; i++) {
        uuid_unparse(server->users[i].uuid, uuidStr);
        offset += sprintf(buffer + offset, "[[\"%s\"] [\"%s\"] [\"%d\"]]\n",
            server->users[i].name, uuidStr,
            is_user_connected(server, server->users[i].uuid));
    }
    send_to_client(server, clientSocket, "%s]\n", buffer);
}

void handle_user_command(server_t *server, int clientSocket, char *command)
{
    (void) server;
    (void) clientSocket;
    (void) command;
}
