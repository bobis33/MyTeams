/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** subscribe_commands
*/

#include "server.h"
#include "commands.h"
#include "utils.h"

#include <string.h>
#include <stdio.h>

void handle_subscribe_command(server_t *server, int clientSocket,
    char *command)
{
    uuid_t team_uuid;
    team_t *team = NULL;

    if (strncmp(command, "/subscribe \"", 12) != 0 || strlen(command) < 51 ||
    command[strlen(command) - 3] != '"')
        return send_to_client(server, clientSocket, "500: Invalid syntax\n");
    else if (!check_user_connection(server, clientSocket))
        return;
    command[strlen(command) - 3] = '\0';
    if (uuid_parse(command + 12, team_uuid) == -1)
        return send_to_client(server, clientSocket, "500: Invalid syntax\n");
    team = search_team_by_uuid(server, team_uuid);
    if (team == NULL)
        return send_to_client(server, clientSocket, "507: Unknown team\n");
    if (!subscribe_user_to_team(team, search_user_by_socket(server,
        clientSocket)))
        return send_to_client(server, clientSocket, "508: already "
            "subscribed\n");
    send_to_client(server, clientSocket, "000: execution success\n");
}

void handle_subscribed_command(server_t *server, int clientSocket,
    char *command)
{
    (void) server;
    (void) clientSocket;
    (void) command;
}

void handle_unsubscribe_command(server_t *server, int clientSocket,
    char *command)
{
    uuid_t team_uuid;
    team_t *team = NULL;

    if (strncmp(command, "/unsubscribe \"", 14) != 0 || strlen(command) < 53 ||
    command[strlen(command) - 3] != '"')
        return send_to_client(server, clientSocket, "500: Invalid syntax\n");
    else if (!check_user_connection(server, clientSocket))
        return;
    command[strlen(command) - 3] = '\0';
    if (uuid_parse(command + 14, team_uuid) == -1)
        return send_to_client(server, clientSocket, "500: Invalid syntax\n");
    team = search_team_by_uuid(server, team_uuid);
    if (team == NULL)
        return send_to_client(server, clientSocket, "507: Unknown team\n");
    if (!unsubscribe_user_to_team(server, team, search_user_by_socket(server,
        clientSocket)))
        return send_to_client(server, clientSocket, "509: not subscribed\n");
    send_to_client(server, clientSocket, "000: execution success\n");
}
