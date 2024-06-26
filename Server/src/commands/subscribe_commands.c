/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** subscribe_commands
*/

#include "server.h"
#include "commands.h"
#include "utils.h"
#include "logging_server.h"

#include <string.h>
#include <stdio.h>
#include <uuid/uuid.h>

static void event_subscribed_unsubscribed(server_t *server, int clientSocket,
    uuid_t team_uuid, bool subscribed)
{
    user_t *user = search_user_by_socket(server, clientSocket);
    char team_uuid_str[37] = {0};
    char user_uuid_str[37] = {0};

    uuid_unparse(team_uuid, team_uuid_str);
    uuid_unparse(user->uuid, user_uuid_str);
    if (subscribed)
        server_event_user_subscribed(team_uuid_str, user_uuid_str);
    else
        server_event_user_unsubscribed(team_uuid_str, user_uuid_str);
}

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
    event_subscribed_unsubscribed(server, clientSocket, team_uuid, true);
}

static void get_team_users(server_t *server, team_t *team, char *user_list)
{
    char user_uuid_str[37] = {0};

    strcat(user_list, "102: user list [");
    for (int i = 0; i < team->users_count; i++) {
        uuid_unparse(team->subscribed_users[i]->uuid, user_uuid_str);
        strcat(user_list, "[\"");
        strcat(user_list, team->subscribed_users[i]->name);
        strcat(user_list, "\"] [\"");
        strcat(user_list, user_uuid_str);
        strcat(user_list, "\"] [\"");
        strcat(user_list, is_user_connected(server,
            team->subscribed_users[i]->uuid) ? "1" : "0");
        strcat(user_list, "\"]]\n");
    }
    strcat(user_list, "]\n");
}

static void reply_team_users(server_t *server, int clientSocket, team_t *team)
{
    char user_list[4096] = {0};

    if (team == NULL)
        return send_to_client(server, clientSocket, "507: Unknown team\n");
    if (!is_user_subscribed_to_team(team, search_user_by_socket(server,
        clientSocket)))
        return send_to_client(server, clientSocket, "510: not subscribed\n");
    get_team_users(server, team, user_list);
    send_to_client(server, clientSocket, "%s", user_list);
}

static void reply_team_list(server_t *server, int clientSocket)
{
    char team_list[4096] = {0};
    char team_uuid_str[37] = {0};

    strcat(team_list, "108: team list [");
    for (int i = 0; i < server->teams_count; i++) {
        uuid_unparse(server->teams[i].uuid, team_uuid_str);
        strcat(team_list, "[\"");
        strcat(team_list, server->teams[i].name);
        strcat(team_list, "\"] [\"");
        strcat(team_list, team_uuid_str);
        strcat(team_list, "\"] [\"");
        strcat(team_list, server->teams[i].description);
        strcat(team_list, "\"]]\n");
    }
    strcat(team_list, "]\n");
    send_to_client(server, clientSocket, "%s", team_list);
}

void handle_subscribed_command(server_t *server, int clientSocket,
    char *command)
{
    uuid_t team_uuid = {0};

    if (strncmp(command, "/subscribed\r\n", 12) == 0) {
        if (!check_user_connection(server, clientSocket))
            return;
        reply_team_list(server, clientSocket);
        return;
    }
    if (strncmp(command, "/subscribed \"", 13) == 0 && strlen(command)
    == 52 && command[49] == '\"') {
        if (!check_user_connection(server, clientSocket))
            return;
        command[49] = '\0';
        if (uuid_parse(command + 13, team_uuid) == -1)
            return send_to_client(server, clientSocket, "500: Invalid"
            " syntax\n");
        reply_team_users(server, clientSocket,
            search_team_by_uuid(server, team_uuid));
    } else
        return send_to_client(server, clientSocket, "500: Invalid syntax\n");
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
    event_subscribed_unsubscribed(server, clientSocket, team_uuid, false);
}
