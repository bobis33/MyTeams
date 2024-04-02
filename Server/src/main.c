/*
** EPITECH PROJECT, 2024
** myteams | server
** File description:
** main.c
*/

#include "server.h"

#include "commands.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>

static const char *commands[] = {
    "/help", "/login", "/logout", "/users", "/user", "/send",
    "/messages", "/subscribe", "/subscribed", "/unsubscribe",
    "/use", "/create", "/list", "/info"
};

static void (*functions[])(server_t *server, int clientSocket,
    char *command) = {
    handle_unimplemented_command, handle_login_command,
    handle_unimplemented_command, handle_unimplemented_command,
    handle_unimplemented_command, handle_unimplemented_command,
    handle_unimplemented_command, handle_unimplemented_command,
    handle_unimplemented_command, handle_unimplemented_command,
    handle_unimplemented_command, handle_unimplemented_command,
    handle_unimplemented_command
};

void handle_unimplemented_command(
    server_t *server, int clientSocket, char *command)
{
    (void) command;
    send_to_client(server, clientSocket, "Error: Command not implemented\n");
}

static char *clear_command(char *command)
{
    for (int i = 0; command[i] != '\0'; i++)
        if (command[i] == '\n')
            command[i] = '\0';
    return command;
}

int handle_client_command(server_t *server, int clientSocket)
{
    char buffer[1024] = {0};
    int readSize = read(clientSocket, buffer, 1024);
    bool commandFound = false;

    if (readSize == 0) {
        kick_client(server, clientSocket);
        return SUCCESS;
    }
    if (readSize == -1)
        return ERROR;
    for (int i = 0; i < 13; i++)
        if (strncmp(buffer, commands[i], strlen(commands[i])) == 0) {
            functions[i](server, clientSocket, buffer);
            return SUCCESS;
        }
    if (!commandFound) {
        send_to_client(server, clientSocket, "Error: Command not found: %s\n",
        clear_command(buffer));
    }
    return SUCCESS;
}

int handle_ready_fd(server_t *server, int fd)
{
    if (fd == server->socket)
        return accept_client(server);
    else
        return handle_client_command(server, fd);
}

int update_server(server_t *server)
{
    fd_set readReadyFds = server->readFds;

    if (select(FD_SETSIZE, &readReadyFds, NULL, NULL, NULL) == -1)
        return ERROR;
    for (int i = 0; i < FD_SETSIZE; i++)
        if (FD_ISSET(i, &readReadyFds))
            return handle_ready_fd(server, i);
    return SUCCESS;
}

int main(int argc, const char *argv[])
{
    server_t server = {0};

    (void) argc;
    (void) argv;
    if (!init_server(&server, 8080))
        return EXIT_ERROR;
    while (!server.shouldStop) {
        if (update_server(&server) == ERROR) {
            shutdown_server(&server);
            return EXIT_ERROR;
        }
    }
    shutdown_server(&server);
    return SUCCESS;
}
