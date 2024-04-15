/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** channel
*/

#include "server.h"

#include <string.h>

channel_t *create_channel(team_t *team, char *channelName, char *description)
{
    channel_t channel = {0};

    if (search_channel_by_name(team, channelName) != NULL)
        return NULL;
    uuid_generate(channel.uuid);
    memcpy(channel.name, channelName, strlen(channelName));
    memcpy(channel.description, description, strlen(description));
    team->channels[team->channels_count] = channel;
    team->channels_count++;
    return &team->channels[team->channels_count - 1];
}

channel_t *search_channel_by_name(team_t *team, char *channelName)
{
    for (int i = 0; i < team->channels_count; i++)
        if (strcmp(team->channels[i].name, channelName) == 0)
            return &team->channels[i];
    return NULL;
}

static channel_t *search_channel_in_team_by_uuid(team_t *team, uuid_t uuid)
{
    for (int i = 0; i < team->channels_count; i++)
        if (uuid_compare(team->channels[i].uuid, uuid) == 0)
            return &team->channels[i];
    return NULL;
}

channel_t *search_channel_by_uuid(server_t *server, uuid_t uuid)
{
    channel_t *channel = NULL;

    for (int i = 0; i < server->teams_count; i++) {
        channel = search_channel_in_team_by_uuid(&server->teams[i], uuid);
        if (channel != NULL)
            return channel;
    }
    return NULL;
}
