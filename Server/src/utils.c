/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** utils
*/

#include "utils.h"
#include "server.h"

#include <string.h>
#include <sys/select.h>

user_t *search_user_by_socket(server_t *server, int clientSocket)
{
    for (int i = 0; i < FD_SETSIZE; i++)
        if (server->clients[i].socket == clientSocket)
            return server->clients[i].user;
    return NULL;
}

user_t *search_user_by_uuid(server_t *server, uuid_t uuid)
{
    for (int i = 0; i < server->usersCount; i++)
        if (uuid_compare(server->users[i].uuid, uuid) == 0)
            return &server->users[i];
    return NULL;
}

user_t *search_user_by_name(server_t *server, char *name)
{
    for (int i = 0; i < server->usersCount; i++)
        if (strcmp(server->users[i].name, name) == 0) {
            return &server->users[i];
        }
    return NULL;
}

bool check_user_connection(server_t *server, int clientSocket)
{
    if (server->clients[clientSocket].user == NULL) {
        send_to_client(server, clientSocket, "502: not logged in\n");
        return false;
    }
    return true;
}

int search_user_client_socket(server_t *server, user_t *user)
{
    for (int i = 0; i < FD_SETSIZE; i++)
        if (server->clients[i].user == user)
            return server->clients[i].socket;
    return -1;
}
