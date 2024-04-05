/*
** EPITECH PROJECT, 2024
** B-NWP-400-BDX-4-1-myteams-yohan.decamps
** File description:
** send_command
*/

#include "commands.h"
#include "server.h"
#include "utils.h"
#include "logging_server.h"

#include <string.h>
#include <uuid/uuid.h>

static bool parse_command(char *command, uuid_t *receiver_uuid, char *message)
{
    char uuidStr[37] = {0};

    if (strncmp(command, "/send \"", 7) != 0 ||
        command[strlen(command) - 3] != '\"' || strlen(command) < 50) {
        return false;
    }
    strncpy(uuidStr, command + 7, 36);
    if (uuid_parse(uuidStr, *receiver_uuid) == -1) {
        return false;
    }
    strncpy(message, command + 46, strlen(command) - 49);
    return true;
}

static void log_event_and_send_response(server_t *server,
    uuid_t receiver_uuid, uuid_t sender_uuid, char *message)
{
    user_t *receiver = search_user_by_uuid(server, receiver_uuid);
    char receiver_uuid_str[37];
    char sender_uuid_str[37];

    uuid_unparse(receiver_uuid, receiver_uuid_str);
    uuid_unparse(sender_uuid, sender_uuid_str);
    server_event_private_message_sended(sender_uuid_str, receiver_uuid_str,
        message);
    send_to_client(server, search_user_client_socket(server, receiver),
    "104: message received [\"%s\"] [\"%s\"]\n", sender_uuid_str, message);
}

void handle_send_command(server_t *server, int clientSocket, char *command)
{
    uuid_t receiver_uuid;
    char message[MAX_BODY_LENGTH] = {0};

    if (!parse_command(command, &receiver_uuid, message)) {
        send_to_client(server, clientSocket, "500: invalid syntax\n");
        return;
    }
    if (!check_user_connection(server, clientSocket))
        return;
    if (!add_message_to_private_discussion(server, search_user_by_socket(
        server, clientSocket), search_user_by_uuid(server, receiver_uuid),
        message)) {
        send_to_client(server, clientSocket, "503: unknown user\n");
        return;
    }
    send_to_client(server, clientSocket, "000: execution success\n");
    log_event_and_send_response(server, receiver_uuid, search_user_by_socket(
        server, clientSocket)->uuid, message);
}
