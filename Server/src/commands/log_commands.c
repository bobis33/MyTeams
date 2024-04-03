/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** log_commands
*/

#include "commands.h"
#include "logging_server.h"
#include "server.h"
#include "utils.h"

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <uuid/uuid.h>

static user_t *create_user(server_t *server, char *username)
{
    user_t *user = &server->users[server->usersCount];

    server->usersCount++;
    for (int i = 0; i < (int) strlen(username) + 1; i++)
        user->name[i] = username[i];
    uuid_generate(user->uuid);
    return user;
}

static void log_event_user_logged_in(char *uuid, bool user_created,
    char *username)
{
    if (user_created)
        server_event_user_created(uuid, username);
    else
        server_event_user_logged_in(uuid);
}

void handle_login_command(server_t *server, int clientSocket, char *command)
{
    user_t *user = NULL;
    char *username = NULL;
    bool user_found = false;
    char uuidStr[37];

    if (strncmp(command, "/login \"", 8) != 0 ||
        command[strlen(command) - 3] != '\"' || strlen(command) < 12) {
        send_to_client(server, clientSocket, "500: invalid syntax\n");
        return;
    }
    username = strtok(command + 7, "\"");
    user = search_user_by_name(server, username);
    user_found = user != NULL;
    if (user == NULL)
        user = create_user(server, username);
    server->clients[clientSocket].user = user;
    uuid_unparse(user->uuid, uuidStr);
    log_event_user_logged_in(uuidStr, !user_found, username);
    send_to_client(server, clientSocket,
        "100: successfully logged in [\"%s\"]\n", uuidStr);
}

void handle_logout_command(server_t *server, int clientSocket, char *command)
{
    char uuidStr[37];

    (void) command;
    if (strncmp(command, "/logout\r\n", 9) != 0) {
        send_to_client(server, clientSocket, "500: invalid syntax\n");
        return;
    }
    if (server->clients[clientSocket].user == NULL) {
        send_to_client(server, clientSocket, "502: not logged in\n");
        return;
    }
    uuid_unparse(server->clients[clientSocket].user->uuid, uuidStr);
    server_event_user_logged_out(uuidStr);
    server->clients[clientSocket].user = NULL;
    send_to_client(server, clientSocket,
        "101: successfully logged out [\"%s\"]\n", uuidStr);
}
