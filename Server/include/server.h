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
#define MAX_USERS 1024

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

typedef struct message_s {
    user_t *author;
    char body[MAX_BODY_LENGTH];
} message_t;

typedef struct private_discussion_s {
    user_t *users[2];
    message_t messages[MAX_PRIVATE_DISCUSSION_MESSAGES];
    int messagesCount;
} private_discussion_t;

typedef struct server_s {
    int socket;
    bool shouldStop;
    client_t clients[FD_SETSIZE];
    fd_set readFds;
    user_t users[MAX_USERS];
    int usersCount;
    private_discussion_t privateDiscussions[MAX_PRIVATE_DISCUSSIONS];
    int privateDiscussionsCount;
} server_t;

bool init_server(server_t *server, int port);
void shutdown_server(server_t *server);

int accept_client(server_t *server);
void kick_client(server_t *server, int clientSocket);
bool check_user_connection(server_t *server, int clientSocket);

__attribute__((format(printf, 3, 4)))
void send_to_client(server_t *server, int clientSocket, char *message, ...);
