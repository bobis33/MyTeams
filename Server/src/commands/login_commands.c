/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** login_commands
*/

#include "commands.h"
#include "server.h"

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <uuid/uuid.h>

static user_t *search_user_by_name(server_t *server, char *name)
{
    for (int i = 0; i < server->usersCount; i++)
        if (strcmp(server->users[i].name, name) == 0) {
            printf("User %s already exists\n", name);
            return &server->users[i];
        }
    printf("User %s not found\n", name);
    return NULL;
}

void handle_login_command(server_t *server, int clientSocket, char *command)
{
    user_t *user = NULL;
    char *username = NULL;

    command += 7;
    username = strtok(command, "\r\n");
    if (username == NULL) {
        send_to_client(server, clientSocket, "Error: Invalid command\n");
        return;
    }
    user = search_user_by_name(server, username);
    if (user == NULL) {
        user = &server->users[server->usersCount];
        server->usersCount++;
        for (int i = 0; i < (int) strlen(username) + 1; i++)
            user->name[i] = username[i];
        uuid_generate(user->uuid);
    }
    server->clients[clientSocket].user = user;
    send_to_client(server, clientSocket, "Successfully logged in\n");
}
