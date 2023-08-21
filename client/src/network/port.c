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


static int port_error(void)
{
    my_put_strerr("Bad arguments: port: 1025 < [port] < 65535\n");
    return ERROR;
}

int is_port(const char *port)
{

    int argsToInt = 0;

    for (register int i = 0, lengthPort = strlen(port); i < lengthPort; i++) {
        if (!isdigit(port[i]))
            return ERROR;
    }

    return (argsToInt = atoi(port)) < PORT_MIN
            || argsToInt > PORT_MAX ? port_error() : argsToInt;

}
