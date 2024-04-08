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

#define MAX_USERS 1024

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

#define MAX_PRIVATE_DISCUSSIONS 255
#define MAX_PRIVATE_DISCUSSION_MESSAGES 1024

typedef struct user_s {
    char name[MAX_NAME_LENGTH];
    uuid_t uuid;
} user_t;

typedef struct client_s {
    int socket;
    user_t *user;
} client_t;

typedef struct private_discussion_message_s {
    uuid_t author_uuid;
    char body[MAX_BODY_LENGTH];
    time_t timestamp;
} private_discussion_message_t;

typedef struct private_discussion_s {
    user_t *user1;
    user_t *user2;
    private_discussion_message_t messages[MAX_PRIVATE_DISCUSSION_MESSAGES];
    int messages_count;
} private_discussion_t;

typedef struct team_s {
    uuid_t uuid;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    user_t *users[MAX_USERS];
    int users_count;
} team_t;

typedef struct server_s {
    int socket;
    bool shouldStop;
    client_t clients[FD_SETSIZE];
    fd_set readFds;
    user_t users[MAX_USERS];
    int usersCount;
    private_discussion_t private_discussions[MAX_PRIVATE_DISCUSSIONS];
    int private_discussions_count;
    team_t teams[MAX_USERS];
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
team_t *get_team_by_name(server_t *server, char *teamName);
team_t *get_team_by_uuid(server_t *server, uuid_t uuid);
bool add_user_to_team(team_t *team, user_t *user);
bool remove_user_from_team(server_t *server, team_t *team, user_t *user);
