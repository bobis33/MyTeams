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

static void reply_team_event(server_t *server, int clientSocket,
    char *team_name, char *team_desc)
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
    reply_team_event(server, clientSocket, team_name, description);
}

static bool parse_create_channel_command(char *command, char *channelName,
    char *description)
{
    char *cName = NULL;
    char *cDesc = NULL;

    if (strncmp(command, "/create \"", 9) != 0 ||
        command[strlen(command) - 3] != '\"' || strlen(command) < 15) {
        return false;
    }
    cName = strtok(command + 9, "\"");
    cDesc = command + 10 + strlen(cName) + 1;
    cDesc = strtok(cDesc, "\"");
    strcpy(channelName, cName);
    strcpy(description, cDesc);
    return true;
}

static void reply_channel_event(server_t *server, team_t *team,
    char *channel_name, char *channel_desc)
{
    char channel_uuid[37] = {0};
    char team_uuid[37] = {0};

    uuid_unparse(search_team_by_uuid(server, team->uuid)->uuid, team_uuid);
    uuid_unparse(team->channels[team->channels_count - 1].uuid, channel_uuid);
    server_event_channel_created(team_uuid, channel_uuid, channel_name);
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->clients[i].socket != 0 && is_user_subscribed_to_team(team,
            search_user_by_socket(server, i))) {
            send_to_client(server, server->clients[i].socket,
            "201: channel created [\"%s\"] [\"%s\"] [\"%s\"]\n", channel_uuid,
            channel_name, channel_desc);
        }
    }
}

static void handle_create_channel_command(server_t *server, int clientSocket,
    char *command)
{
    char channel_name[MAX_NAME_LENGTH] = {0};
    char description[MAX_DESCRIPTION_LENGTH] = {0};
    team_t *team = NULL;
    char channel_uuid[37] = {0};

    if (!parse_create_channel_command(command, channel_name, description)) {
        send_to_client(server, clientSocket, "500: invalid syntax\n");
        return;
    }
    if (!check_user_connection(server, clientSocket))
        return;
    team = search_team_by_uuid(server,
        server->clients[clientSocket].context_uuid);
    if (create_channel(team, channel_name, description) == NULL)
        return send_to_client(server, clientSocket, "511: a channel with this"
            " name already exists");
    reply_channel_event(server, team, channel_name, description);
    uuid_unparse(team->channels[team->channels_count - 1].uuid, channel_uuid);
    send_to_client(server, clientSocket, "109: channel created [\"%s\"]\n",
        channel_uuid);
}

static bool parse_create_thread_command(char *command, char *thread_title,
    char *thread_body)
{
    char *title = NULL;
    char *body = NULL;

    if (strncmp(command, "/create \"", 9) != 0 ||
        command[strlen(command) - 3] != '\"' || strlen(command) < 15) {
        return false;
    }
    title = strtok(command + 9, "\"");
    body = command + 10 + strlen(title) + 1;
    body = strtok(body, "\"");
    strcpy(thread_title, title);
    strcpy(thread_body, body);
    return true;
}

// TODO: use multiple context uuids
static void handle_create_thread_command(server_t *server, int clientSocket,
    char *command)
{
    char thread_title[MAX_NAME_LENGTH] = {0};
    char body[MAX_BODY_LENGTH] = {0};

    if (!parse_create_thread_command(command, thread_title, body)) {
        send_to_client(server, clientSocket, "500: invalid syntax\n");
        return;
    }
    if (!check_user_connection(server, clientSocket))
        return;
    send_to_client(server, clientSocket, "thread title: %s\nbody: %s\n",
        thread_title, body);
}

static void handle_create_reply_command(server_t *server, int clientSocket,
    char *command)
{
    (void) server;
    (void) clientSocket;
    (void) command;
}

void handle_create_command(server_t *server, int clientSocket, char *command)
{
    if (server->clients[clientSocket].context == NONE)
        return handle_create_team_command(server, clientSocket, command);
    if (server->clients[clientSocket].context == TEAM)
        return handle_create_channel_command(server, clientSocket, command);
    if (server->clients[clientSocket].context == CHANNEL)
        return handle_create_thread_command(server, clientSocket, command);
    if (server->clients[clientSocket].context == THREAD)
        return handle_create_reply_command(server, clientSocket, command);
    return;
}
