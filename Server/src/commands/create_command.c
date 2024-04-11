/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** create_command
*/

#include "logging_server.h"
#include "server.h"
#include "commands.h"
#include "utils.h"

#include <string.h>
#include <sys/select.h>
#include <stdio.h>

static bool parse_create_team_command(char *command, char *teamName,
    char *description)
{
    char *tName = NULL;
    char *tDesc = NULL;

    if (strncmp(command, "/create \"", 9) != 0 ||
        command[strlen(command) - 3] != '\"' || strlen(command) < 15) {
        return false;
    }
    tName = strtok(command + 9, "\"");
    tDesc = command + 10 + strlen(tName) + 1;
    tDesc = strtok(tDesc, "\"");
    strcpy(teamName, tName);
    strcpy(description, tDesc);
    return true;
}

static void reply_event(server_t *server, int clientSocket, char *team_name,
    char *team_desc)
{
    char team_uuid[37] = {0};
    char user_uuid[37] = {0};

    uuid_unparse(search_user_by_socket(server, clientSocket)->uuid, user_uuid);
    uuid_unparse(server->teams[server->teams_count - 1].uuid, team_uuid);
    send_to_client(server, clientSocket, "107: team created [\"%s\"]\n",
        team_uuid);
    server_event_team_created(team_uuid, team_name, user_uuid);
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->clients[i].socket != 0) {
            send_to_client(server, server->clients[i].socket,
            "200: team created [\"%s\"] [\"%s\"] [\"%s\"]\n", team_uuid,
            team_name, team_desc);
        }
    }
}

static void handle_create_team_command(server_t *server, int clientSocket,
    char *command)
{
    char team_name[MAX_NAME_LENGTH] = {0};
    char description[MAX_DESCRIPTION_LENGTH] = {0};

    if (!parse_create_team_command(command, team_name, description)) {
        send_to_client(server, clientSocket, "500: invalid syntax\n");
        return;
    }
    if (!check_user_connection(server, clientSocket))
        return;
    if (create_team(server, team_name, description) == NULL) {
        send_to_client(server, clientSocket, "505: a team with this"
        " name already exists\n");
        return;
    }
    subscribe_user_to_team(&server->teams[server->teams_count - 1],
        search_user_by_socket(server, clientSocket));
    reply_event(server, clientSocket, team_name, description);
}

void handle_create_command(server_t *server, int clientSocket, char *command)
{
    if (true)
        handle_create_team_command(server, clientSocket, command);
}
