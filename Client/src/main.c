/*
** EPITECH PROJECT, 2024
** myteams | client
** File description:
** main.c
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>

#include "client.h"

static void print_help(void)
{
    write(1, "USAGE: ./myteams_cli ip port\n\tip\tis the server ip address "
             "on which the server socket listens\n\tport\tis the port number "
             "on which the server socket listens\n", 153);
}

int check_argv(const char *ip, const char *port)
{
    struct sockaddr_in socket;
    int inet_pton_return = 0;

    if (atoi(port) < 1024 || atoi(port) > 65535) {
        write(2, "Port must be between 1024 and 65535\n", 36);
        return ERROR;
    }
    inet_pton_return = inet_pton(AF_INET, ip, &socket.sin_addr);
    if (inet_pton_return < 0) {
        perror("inet_pton");
        return ERROR;
    } else if (inet_pton_return == 0) {
        write(2, "Error: ip_adress: Does not contain a character "
                 "string representing a valid network address\n", 91);
        return ERROR;
    } else {
        return SUCCESS;
    }
}

int main(int argc, const char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "-help") == 0) {
        print_help();
        return SUCCESS;
    } else if (argc == 3) {
        if (check_argv(argv[1], argv[2]) == ERROR)
            return EPITECH_ERROR;
    }
    return EPITECH_ERROR;
}
