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
#include <signal.h>
#include <stdlib.h>

static const char *commands[] = {
    "/help", "/login", "/logout", "/users", "/user", "/send",
    "/messages", "/subscribe", "/subscribed", "/unsubscribe",
    "/use", "/create", "/list", "/info", "/stop"
};

static void (*functions[])(server_t *server, int clientSocket,
    char *command) = {
    handle_help_command,            // help,
    handle_login_command,           // login,
    handle_logout_command,          // logout,
    handle_users_command,           // users,
    handle_user_command,            // user,
    handle_send_command,            // send,
    handle_messages_command,        // messages,
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
    if (!commandFound)
        send_to_client(server, clientSocket, "501: unknown command\n");
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
    if ((argc != 2 || atoi(argv[1]) < 1024) ||
        !init_server(&server, atoi(argv[1])))
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

/* Server log events:
    server_event_team_created            - NO
    server_event_channel_created         - NO
    server_event_thread_created          - NO
    server_event_reply_created           - NO
    server_event_user_subscribed         - NO
    server_event_user_unsubscribed       - NO
    server_event_user_created            - YES
    server_event_user_loaded             - YES
    server_event_user_logged_in          - YES
    server_event_user_logged_out         - YES
    server_event_private_message_sended  - YES
*/

/* Client log events:
    client_event_logged_in                       - YES
    client_event_logged_out                      - YES
    client_event_private_message_received        - YES
    client_event_thread_reply_received           - NO
    client_event_team_created                    - NO
    client_event_channel_created                 - NO
    client_event_thread_created                  - NO
    client_print_users                           - YES
    client_print_teams                           - NO
    client_team_print_channels                   - NO
    client_channel_print_threads                 - NO
    client_thread_print_replies                  - NO
    client_private_message_print_messages        - YES
    client_error_unknown_team                    - NO
    client_error_unknown_channel                 - NO
    client_error_unknown_thread                  - NO
    client_error_unknown_user                    - YES
    client_error_unauthorized                    - YES
    client_error_already_exist                   - YES
    client_print_user                            - YES
    client_print_team                            - NO
    client_print_channel                         - NO
    client_print_thread                          - NO
    client_print_team_created                    - NO
    client_print_channel_created                 - NO
    client_print_thread_created                  - NO
    client_print_reply_created                   - NO
    client_print_subscribed                      - NO
    client_print_unsubscribed                    - NO
*/

/* Commands:
    /help : show help                                        - YES
    /login [“user_name”]                                     - YES
    /logout                                                  - YES
    /users                                                   - YES
    /user [“user_uuid”]                                      - YES
    /send [“user_uuid”] [“message_body”]                     - YES
    /messages [“user_uuid”]                                  - YES
    /subscribe [“team_uuid”]                                 - NO
    /subscribed ?[“team_uuid”]                               - NO
    /unsubscribe [“team_uuid”]                               - NO
    /use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”]   - NO
    /create                                                  - NO
    /list                                                    - NO
    /info                                                    - NO
*/
