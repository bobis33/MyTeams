/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** thread
*/

#include "server.h"

#include <string.h>

thread_t *create_thread(channel_t *channel, char *title, char *body,
    user_t *author)
{
    thread_t thread = {0};

    if (search_thread_by_title(channel, title) != NULL)
        return NULL;
    uuid_generate(thread.uuid);
    memcpy(thread.title, title, strlen(title));
    memcpy(thread.body, body, strlen(body));
    thread.author = author;
    thread.timestamp = time(NULL);
    channel->threads[channel->threads_count] = thread;
    channel->threads_count++;
    return &channel->threads[channel->threads_count - 1];
}

thread_t *search_thread_by_uuid(channel_t *channel, uuid_t uuid)
{
    for (int i = 0; i < channel->threads_count; i++)
        if (uuid_compare(channel->threads[i].uuid, uuid) == 0)
            return &channel->threads[i];
    return NULL;
}

thread_t *search_thread_by_title(channel_t *channel, char *title)
{
    for (int i = 0; i < channel->threads_count; i++)
        if (strcmp(channel->threads[i].title, title) == 0)
            return &channel->threads[i];
    return NULL;
}
