/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** private_discussion
*/

#include "server.h"

#include <string.h>
#include <uuid/uuid.h>
#include <stdio.h>

void create_private_discussion(server_t *server, user_t *user1, user_t *user2)
{
    private_discussion_t private_discussion = {0};

    private_discussion.user1 = user1;
    private_discussion.user2 = user2;
    memset(private_discussion.messages, 0,
        sizeof(private_discussion.messages));
    server->private_discussions[server->private_discussions_count] =
        private_discussion;
    server->private_discussions_count++;
}

private_discussion_t *get_private_discussion(server_t *server, user_t *user1,
    user_t *user2)
{
    for (int i = 0; i < server->private_discussions_count; i++) {
        if (server->private_discussions[i].user1 == user1 &&
            server->private_discussions[i].user2 == user2) {
            return &server->private_discussions[i];
        }
        if (server->private_discussions[i].user1 == user2 &&
            server->private_discussions[i].user2 == user1) {
            return &server->private_discussions[i];
        }
    }
    create_private_discussion(server, user1, user2);
    return &server->private_discussions[server->private_discussions_count - 1];
}

bool add_message_to_private_discussion(server_t *server, user_t *author,
    user_t *receiver, char *message)
{
    private_discussion_message_t private_discussion_message = {0};
    private_discussion_t *private_discussion =
        get_private_discussion(server, author, receiver);

    if (!author || !receiver || !message) {
        printf("Error: add_message_to_private_discussion\n");
        return false;
    }
    memcpy(private_discussion_message.author_uuid, author->uuid,
        sizeof(uuid_t));
    private_discussion_message.timestamp = time(NULL);
    memset(private_discussion_message.body, 0,
        sizeof(private_discussion_message.body));
    strncpy(private_discussion_message.body, message, strlen(message));
    private_discussion->messages[private_discussion->messages_count] =
        private_discussion_message;
    private_discussion->messages_count++;
    return true;
}
