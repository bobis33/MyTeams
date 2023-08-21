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


static int ip_error(void)
{
    my_put_str("Bad arguments: ip_adress: ");
    perror("inet_pton");
    return ERROR;
}

int is_ip(const char *ip)
{

    struct sockaddr_in sa;

    return inet_pton(AF_INET, ip, &(sa.sin_addr)) != 1 ? ip_error() : SUCCESS;
}
