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
