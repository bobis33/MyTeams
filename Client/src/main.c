/*
** EPITECH PROJECT, 2024
** myteams | client
** File description:
** main.c
*/

#include <string.h>

#include "client.h"

static void print_help(void)
{
    write(1, "USAGE: ./myteams_cli ip port\n\tip\tis the server ip address "
        "on which the server socket listens\n\tport\tis the port number "
        "on which the server socket listens\n", 153);
}

int main(int argc, const char *argv[])
{
    struct client *client = malloc(sizeof(struct client));

    if (argc == 2 && strcmp(argv[1], "-help") == 0) {
        print_help();
        return SUCCESS;
    } else if (argc == 3) {
        return parse_args(argv[1], argv[2], client) == ERROR ?
            EPITECH_ERROR : run_client(client);
    }
    return EPITECH_ERROR;
}
