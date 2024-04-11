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

// channel_t *channel = search_channel_by_uuid(server, context_uuid);
// thread_t *thread = search_thread_by_uuid(server, context_uuid);
static bool update_context(server_t *server, int clientSocket,
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
        command[42] == '"') {
        if (!check_user_connection(server, clientSocket))
            return;
        if (update_context(server, clientSocket, command + 6))
            send_to_client(server, clientSocket, "000: execution success\n");
        else
            send_to_client(server, clientSocket, "506: invalid context\n");
        return;
    }
    send_to_client(server, clientSocket, "500: invalid syntax\n, %c\n",
        command[42]);
}
