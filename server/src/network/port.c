/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** port
*/

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

int is_port(const char *args)
{

    int argsToInt = 0;

    for (register int i = 0, n = strlen(args); i < n; i++) {
        if (!isdigit(args[i]))
            return port_error();
    }

    return (argsToInt = atoi(args)) < PORT_MIN
            || argsToInt > PORT_MAX ? port_error() : argsToInt;

}
