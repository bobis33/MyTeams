/*
** EPITECH PROJECT, 2024
** myftp | client
** File description:
** client.h
*/

#pragma once

#include <netinet/in.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "logging_client.h"

#define SUCCESS 0
#define ERROR -1
#define EPITECH_ERROR 84

#define MAX_CHAR_SIZE 1024

typedef struct client_s {
    uint16_t port;
    char *ip;
    int sockfd;
    struct sockaddr_in socket_address;
} client_t;

int parse_args(const char *ip, const char *port, client_t *client);

int run_client(client_t *client);
