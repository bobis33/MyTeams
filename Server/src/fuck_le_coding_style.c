/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** fuck_le_coding_style
*/

#include "server.h"

#include <uuid/uuid.h>

bool is_user_subscribed_to_team(team_t *team, user_t *user)
{
    for (int i = 0; i < team->users_count; i++)
        if (uuid_compare(team->subscribed_users[i]->uuid, user->uuid) == 0)
            return true;
    return false;
}

bool is_user_connected(server_t *server, uuid_t user_uuid)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->clients[i].user != NULL &&
            uuid_compare(server->clients[i].user->uuid, user_uuid) == 0) {
            return true;
        }
    }
    return false;
}
