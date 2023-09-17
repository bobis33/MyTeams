/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** port
*/

//SYSTEMS INCLUDES
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//LOCALES INCLUDES
#include "constants.h"
#include "utils.h"


static const int port_error(void)
{
    my_put_strerr("Bad arguments: port: 1025 < [port] < 65535\n");
    return ERROR;
}

int is_port(const char *port)
{

    int portAsInteger = 0;

    for (register int i = 0, n = strlen(port); i < n; i++) {
        if (!isdigit(port[i]))
            return port_error();
    }

    return (portAsInteger = atoi(port)) < PORT_MIN
            || portAsInteger > PORT_MAX ? port_error() : portAsInteger;

}
