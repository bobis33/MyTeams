/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** misc_commands
*/

#include "server.h"
#include "commands.h"

void handle_stop_server_command(server_t *server, int clientSocket,
    char *command)
{
    (void) command;
    (void) clientSocket;
    server->shouldStop = true;
}

void handle_unimplemented_command(server_t *server, int clientSocket,
    char *command)
{
    (void) command;
    send_to_client(server, clientSocket, "Error: Command not implemented\n");
}
