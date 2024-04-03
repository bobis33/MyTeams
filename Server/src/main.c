/*
** EPITECH PROJECT, 2024
** myteams | server
** File description:
** main.c
*/

#include "server.h"
#include "commands.h"
#include "utils.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

static const char *commands[] = {
    "/help", "/login", "/logout", "/users", "/user", "/send",
    "/messages", "/subscribe", "/subscribed", "/unsubscribe",
    "/use", "/create", "/list", "/info", "/stop"
};

static void (*functions[])(server_t *server, int clientSocket,
    char *command) = {
    handle_unimplemented_command,   // help,
    handle_login_command,           // login,
    handle_logout_command,          // logout,
    handle_users_command,           // users,
    handle_unimplemented_command,   // user,
    handle_unimplemented_command,   // send,
    handle_unimplemented_command,   // messages,
    handle_unimplemented_command,   // subscribe,
    handle_unimplemented_command,   // subscribed,
    handle_unimplemented_command,   // unsubscribe,
    handle_unimplemented_command,   // use,
    handle_unimplemented_command,   // create,
    handle_unimplemented_command,   // list,
    handle_unimplemented_command,   // info,
    handle_stop_server_command      // stop
};

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
    for (int i = 0; i < 15; i++)
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

static bool *stop_signal_catched(void)
{
    static bool globalStop = false;

    return &globalStop;
}

static void my_handler(int signal)
{
    (void) signal;
    *stop_signal_catched() = true;
}

int main(int argc, const char *argv[])
{
    server_t server = {0};
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
    (void) argc;
    (void) argv;
    if (!init_server(&server, 8080))
        return EXIT_ERROR;
    while (!server.shouldStop && !*stop_signal_catched()) {
        if (update_server(&server) == ERROR) {
            shutdown_server(&server);
            return EXIT_ERROR;
        }
    }
    shutdown_server(&server);
    return SUCCESS;
}
