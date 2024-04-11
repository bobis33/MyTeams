/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** teams
*/

#include "server.h"

#include <stdlib.h>
#include <string.h>

team_t *create_team(server_t *server, char *teamName, char *description)
{
    team_t team = {0};

    if (search_team_by_name(server, teamName) != NULL)
        return NULL;
    uuid_generate(team.uuid);
    memcpy(team.name, teamName, strlen(teamName));
    memcpy(team.description, description, strlen(description));
    server->teams[server->teams_count] = team;
    server->teams_count++;
    return &server->teams[server->teams_count - 1];
}

team_t *search_team_by_name(server_t *server, char *teamName)
{
    for (int i = 0; i < server->teams_count; i++)
        if (strcmp(server->teams[i].name, teamName) == 0)
            return &server->teams[i];
    return NULL;
}

team_t *search_team_by_uuid(server_t *server, uuid_t uuid)
{
    for (int i = 0; i < server->teams_count; i++)
        if (uuid_compare(server->teams[i].uuid, uuid) == 0)
            return &server->teams[i];
    return NULL;
}

bool add_user_to_team(team_t *team, user_t *user)
{
    for (int i = 0; i < team->users_count; i++)
        if (team->users[i] == user)
            return false;
    team->users[team->users_count] = user;
    team->users_count++;
    return true;
}

static void move_users_down(server_t *server, int index)
{
    for (int i = index; i < server->teams_count - 1; i++)
        server->teams[i] = server->teams[i + 1];
}

bool remove_user_from_team(server_t *server, team_t *team, user_t *user)
{
    for (int i = 0; i < team->users_count; i++)
        if (team->users[i] == user) {
            move_users_down(server, i);
            team->users_count--;
            return true;
        }
    return false;
}
