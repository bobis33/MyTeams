#!/bin/bash

RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
NC=$(tput sgr0)
CLIENT_PATH="./client/myteams_cli" 

handle_compilation_error() {
    echo "${RED}Compilation failed. Here are the errors:${NC}"
    cat $1
    rm $1
    exit 1
}

echo
echo "${GREEN}Compiling in progress . . .${NC}"

compil_logs=$(mktemp)

make > $compil_logs 2>&1

if [ $? -ne 0 ]; then
    handle_compilation_error $compil_logs
else
    echo "${GREEN}Compilation successful !${NC}"
    rm $compil_logs
fi

echo
echo "Which ip ?"
read ip

echo
echo "Which port ?"
read port
echo

echo "${GREEN}Launching the client . . .${NC}"
echo

$CLIENT_PATH $ip $port
