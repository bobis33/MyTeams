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

static void log_event_user_logged_in(uuid_t uuid, bool user_created,
    char *username)
{
    char uuidStr[37];

    uuid_unparse(uuid, uuidStr);
    if (user_created)
        server_event_user_created(uuidStr, username);
    else
        server_event_user_logged_in(uuidStr);
}

void handle_login_command(server_t *server, int clientSocket, char *command)
{
    user_t *user = NULL;
    char *username = NULL;
    bool user_found = false;

    command += 7;
    username = strtok(command, "\r\n");
    if (username == NULL || server->clients[clientSocket].user != NULL) {
        send_to_client(server, clientSocket, "Error: Invalid command or "\
        "you are already logged in\n");
        return;
    }
    user = search_user_by_name(server, username);
    user_found = user != NULL;
    if (user == NULL)
        user = create_user(server, username);
    server->clients[clientSocket].user = user;
    log_event_user_logged_in(user->uuid, !user_found, username);
    send_to_client(server, clientSocket, "Successfully logged in\n");
}

void handle_logout_command(server_t *server, int clientSocket, char *command)
{
    char uuidStr[37];

    (void) command;
    if (server->clients[clientSocket].user == NULL) {
        send_to_client(server, clientSocket, "Error: You are not logged in\n");
        return;
    }
    send_to_client(server, clientSocket, "Successfully logged out\n");
    uuid_unparse(server->clients[clientSocket].user->uuid, uuidStr);
    server_event_user_logged_out(uuidStr);
    server->clients[clientSocket].user = NULL;
}
