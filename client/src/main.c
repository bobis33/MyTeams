/*
** EPITECH PROJECT, 2023
** myTeams
** File description:
** main
**
** Copyright 2023 Masina Elliot and contributors
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

//SYSTEMS INCLUDES

//LOCALES INCLUDES
#include "constants.h"
#include "error.h"
#include "client.h"


/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return non-zéro value if code of error 
 */

int main(int argc, char *argv[])
{

    int checkArgsValue = 0;

    return (checkArgsValue = check_args(argc, argv[1], argv[2])) ==
    ERROR ? EPITECH_ERROR : run_client(argv[1], checkArgsValue);

}
