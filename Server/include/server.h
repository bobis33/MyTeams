/*
** EPITECH PROJECT, 2024
** myftp | server
** File description:
** server.h
*/

#pragma once

#include <sys/select.h>
#include <stdbool.h>
#include <uuid/uuid.h>

#define SUCCESS 0
#define ERROR -1
#define EXIT_ERROR 84

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

typedef struct user_s {
    char name[MAX_NAME_LENGTH];
    uuid_t uuid;
} user_t;

typedef enum context_e {
    NONE = 0,
    TEAM = 1,
    CHANNEL = 2,
    THREAD = 3
} context_t;

typedef struct client_s {
    int socket;
    user_t *user;
    uuid_t context_uuid;
    context_t context;
} client_t;

typedef struct private_discussion_message_s {
    uuid_t author_uuid;
    char body[MAX_BODY_LENGTH];
    time_t timestamp;
} private_discussion_message_t;

#define MAX_PRIVATE_DISCUSSION_MESSAGES 200
typedef struct private_discussion_s {
    user_t *user1;
    user_t *user2;
    private_discussion_message_t messages[MAX_PRIVATE_DISCUSSION_MESSAGES];
    int messages_count;
} private_discussion_t;

typedef struct thread_s {
    uuid_t uuid;
    char title[MAX_NAME_LENGTH];
    char body[MAX_BODY_LENGTH];
    user_t *author;
    time_t timestamp;
} thread_t;

typedef struct channel_s {
    uuid_t uuid;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    thread_t threads[50];
    int threads_count;
} channel_t;

typedef struct team_s {
    uuid_t uuid;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    user_t *subscribed_users[50];
    int users_count;
    channel_t channels[20];
    int channels_count;
} team_t;

typedef struct server_s {
    int socket;
    bool shouldStop;
    client_t clients[FD_SETSIZE];
    fd_set readFds;
    user_t users[100];
    int usersCount;
    private_discussion_t private_discussions[200];
    int private_discussions_count;
    team_t teams[50];
    int teams_count;
} server_t;

bool init_server(server_t *server, int port);
void shutdown_server(server_t *server);

int accept_client(server_t *server);
void kick_client(server_t *server, int clientSocket);

__attribute__((format(printf, 3, 4)))
void send_to_client(server_t *server, int clientSocket, char *message, ...);

private_discussion_t *get_private_discussion(server_t *server, user_t *user1,
    user_t *user2);
bool add_message_to_private_discussion(server_t *server, user_t *author,
    user_t *receiver, char *message);

team_t *create_team(server_t *server, char *teamName, char *description);
team_t *search_team_by_name(server_t *server, char *teamName);
team_t *search_team_by_uuid(server_t *server, uuid_t uuid);
bool subscribe_user_to_team(team_t *team, user_t *user);
bool unsubscribe_user_to_team(server_t *server, team_t *team, user_t *user);
bool is_user_subscribed_to_team(team_t *team, user_t *user);

channel_t *create_channel(team_t *team, char *channelName, char *description);
channel_t *search_channel_by_name(team_t *team, char *channelName);
channel_t *search_channel_by_uuid(server_t *server, uuid_t uuid);

thread_t *create_thread(channel_t *channel, char *title, char *body,
    user_t *author);
thread_t *search_thread_by_uuid(channel_t *channel, uuid_t uuid);
thread_t *search_thread_by_title(channel_t *channel, char *title);
