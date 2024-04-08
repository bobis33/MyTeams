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

static bool parse_command(char *command, char *teamName, char *description)
{
    if (strncmp(command, "/create \"", 9) != 0 ||
        command[strlen(command) - 3] != '\"' || strlen(command) < 15) {
        return false;
    }
    strncpy(teamName, command + 9, strlen(command) - 12);
    strncpy(description, command + 9 + strlen(teamName) + 3,
        strlen(command) - 12 - strlen(teamName));
    return true;
}

void handle_create_command(server_t *server, int clientSocket, char *command)
{
    char team_name[MAX_NAME_LENGTH] = {0};
    char description[MAX_DESCRIPTION_LENGTH] = {0};
    char uuid[37] = {0};

    if (!parse_command(command, team_name, description)) {
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
    add_user_to_team(&server->teams[server->teams_count - 1],
        search_user_by_socket(server, clientSocket));
    uuid_unparse(server->teams[server->teams_count - 1].uuid, uuid);
    send_to_client(server, clientSocket, "107: team created [\"%s\"]\n", uuid);
    server_event_team_created(uuid, team_name, description);
}
