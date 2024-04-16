/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** use_command
*/

#include "server.h"
#include "commands.h"
#include "utils.h"

#include <uuid/uuid.h>
#include <string.h>
#include <stdio.h>

static bool update_team_context(server_t *server, int clientSocket,
    char *context_uuid_str)
{
    team_t *team = NULL;
    uuid_t context_uuid;

    context_uuid_str[36] = '\0';
    if (uuid_parse(context_uuid_str, context_uuid) == -1)
        return false;
    team = search_team_by_uuid(server, context_uuid);
    if (team != NULL) {
        uuid_copy(server->clients[clientSocket].context_uuid, context_uuid);
        server->clients[clientSocket].context = TEAM;
        return true;
    }
    return false;
}

static void handle_use_team(server_t *server, int clientSocket, char *command)
{
    if (!check_user_connection(server, clientSocket))
        return;
    if (update_team_context(server, clientSocket, command + 6))
        send_to_client(server, clientSocket, "000: execution success\n");
    else
        send_to_client(server, clientSocket, "506: invalid context\n");
}

static void handle_use_thread(server_t *server, int clientSocket,
    char *command)
{
    if (!check_user_connection(server, clientSocket))
        return;
    (void) command;
}

static bool update_channel_context(server_t *server, int clientSocket,
    char *command)
{
    uuid_t team_context_uuid;
    channel_t *channel = NULL;
    uuid_t channel_context_uuid;

    command[36] = '\0';
    if (uuid_parse(command, team_context_uuid) == -1 ||
        !search_team_by_uuid(server, team_context_uuid))
        return false;
    command[75] = '\0';
    if (uuid_parse(command + 39, channel_context_uuid) == -1)
        return false;
    channel = search_channel_by_uuid(server, channel_context_uuid);
    if (channel != NULL) {
        uuid_copy(server->clients[clientSocket].context_uuid,
            channel_context_uuid);
        server->clients[clientSocket].context = CHANNEL;
        return true;
    }
    return false;
}

static void handle_use_channel(server_t *server, int clientSocket,
    char *command)
{
    if (!check_user_connection(server, clientSocket))
        return;
    if (update_channel_context(server, clientSocket, command + 6))
        send_to_client(server, clientSocket, "000: execution success\n");
    else
        send_to_client(server, clientSocket, "506: invalid context\n");
}

// TODO: check if the user is subscribed to the team
void handle_use_command(server_t *server, int clientSocket, char *command)
{
    if (strncmp(command, "/use\n", strlen("/use\n")) == 0) {
        if (!check_user_connection(server, clientSocket))
            return;
        server->clients[clientSocket].context = NONE;
        send_to_client(server, clientSocket, "500: invalid syntax\n");
        return;
    }
    if (strncmp(command, "/use \"", 6) == 0 && strlen(command) == 45 &&
        command[42] == '"')
        return handle_use_team(server, clientSocket, command);
    if (strncmp(command, "/use \"", 6) == 0 && strlen(command) == 84 &&
        command[81] == '"')
        return handle_use_channel(server, clientSocket, command);
    if (strncmp(command, "/use \"", 6) == 0 && strlen(command) == 123 &&
        command[120] == '"')
        return handle_use_thread(server, clientSocket, command);
    send_to_client(server, clientSocket, "500: invalid syntax\n");
}
