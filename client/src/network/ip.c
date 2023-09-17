/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** ip
*/

//SYSTEMES INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

//LOCALES INCLUDES
#include "constants.h"
#include "utils.h"

static const int ip_error(const int error_value)
{
    my_put_strerr("Bad arguments: ip_adress: ");

    if (error_value == 0)
        my_put_strerr("Does not contain a character string representing "
        "a valid network address in the specified address family.\n");
    if (error_value == -1)
        perror("inet_pton");
    return ERROR;
}

int is_ip(const char *ip)
{

    struct sockaddr_in sa;
    int error_value = 0;

    return (error_value = inet_pton(AF_INET,
                                ip,
                                &(sa.sin_addr))) != 1 ? ip_error(error_value)
                                                        : SUCCESS;
}
