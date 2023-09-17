/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** main
*/

//SYSTEMS INCLUDES

//LOCALES INCLUDES
#include "constants.h"
#include "error.h"
#include "client.h"

int main(int argc, char *argv[])
{

    int checkArgsValue = 0;

    return (checkArgsValue = check_args(argc, argv[1], argv[2])) ==
    ERROR ? EPITECH_ERROR : run_client(argv[1], checkArgsValue);

}
