
# EPITECH PROJECT - [Network Programming] My_teams

### The goal of this project is to create a server and a CLI client.


<details>
  <summary>Table of Contents</summary>

  - [Getting started](#getting-started)
    - [Prerequisites](#prerequisites)
      - [OS](#os)
      - [Libraries](#libraries)
      - [Compiler](#compiler)
    - [Installation](#installation)
  - [Architecture](#architecture)
  - [Using MyTeams](#using-myteams)
    - [Launch MyTeams](#launch-myteams)
      - [With scripts](#with-scripts)
        - [Launch server](#launch-server)
        - [Launch client](#launch-client)
      - [With make](#with-make)
        - [Compile project](#compile-project)
        - [Launch server](#launch-server)
        - [Launch client](#launch-client)
      - [Further details](#details)
    - [Server](#server)
      - [Features](#features)
      - [Security](#security)
    - [Client](#client)
      - [Features](#features)
        - [/create](#create)
        - [/list](#list)
        - [/info](#info)
      - [Informations](#informations)
    - [Tests](#tests)
  - [Documentation](#documentation)
    - [Doxygen](#doxygen)
  - [Uninstalling MyTeams](#uninstalling-myteams)
  - [Contributors](#contributors)
  - [License](#license)


</details>

## Getting started

### Prerequisites

* #### OS

  A Unix-like operating system: macOS, Linux.

* #### Libraries

  GNU C Library (https://www.gnu.org/software/libc/)

  Libuuid (https://linux.die.net/man/3/libuuid)

* #### Compiler

  GNU Make (https://www.gnu.org/software/make/)

### Installation

  | Method    | Command                                                         |
  | :-------- | :-------------------------------------------------------------- |
  | **git**   | `git clone [le repo]` |

## Architecture



    MyTeams
    │
    │─ .github/workflows/       workflows
    │
    │─ client/                  client source code
    │
    │─ doc/                     subject, Epitech coding style and Doxygen documentation.
    │
    │─ scripts/                 useful scripts to use the project
    │
    └─ server/                  server source code

## Using MyTeams

* ### Launch MyTeams

  * #### With scripts

      ```
      cd MyTeams/
      ```
      * ##### Launch server
        ```
        ./scripts/server.sh
        ```
      * ##### Launch client
        ```
        ./scripts/client.sh
        ```

  * #### With make

    * ##### Compile project
 
      ```
      cd MyTeams/
      ```
      ```
      make
      ```

    * ##### Launch server

      ```
      ./server/server [port]
      ```

    * ##### Launch client

      ```
      ./client/client [ip] [port]
      ```
  * #### Further details

    ```
    ./client/client -help
    ```

    ```
    ./server/server -help
    ```

* ### Server

  * #### Features

    The server is able to handle several clients.

    When the server shutdown it save internal information.
    When the server start it look if the save exist and load it.

    The server will print every requested events on the standard error output.
    In specific case some informations can be displayed on the standart output.

  * #### Security

    There is no password authentication required.

* ### Client

  * #### Features

    ```
    /help
    ```
    show help

    ```
    /login [“user_name”]
    ```
    set the user_name used by client


    ```
    /logout
    ```
    disconnect the client from the server


    ```
    /users
    ```
    get the list of all users that exist on the domain


    ```
    /user [“user_uuid”]
    ```
    get information about a user


    ```
    /send [“user_uuid”] [“message_body”]
    ```
    send a message to a user


    ```
    /messages [“user_uuid”]
    ```
    list all messages exchange with an user


    ```
    /subscribe [“team_uuid”]
    ```
    subscribe to the event of a team and its sub directories (enable reception of all events from a team)


    ```
    /subscribed ?[“team_uuid”]
    ```
    list all subscribed teams or list all users subscribed to a team


    ```
    /unsubscribe [“team_uuid”]
    ```
    unsubscribe from a team


    ```
    /use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”] 
    ```
    use specify a context team/channel/thread


    ```
    /create
    ```
    based on what is being used create the sub resource


    ```
    /list
    ```
    based on what is being used list all the sub resources


    ```
    /info
    ```
    based on what is being used list the current

    * ##### /Create
      When the context is not defined (/use):
        ```
        /create [“team_name”] [“team_description”] : create a new team
        ```
      When team_uuid is defined (/use “team_uuid”):
        ```
        /create [“channel_name”] [“channel_description”] : create a new channel
        ```
      When team_uuid and channel_uuid are defined (/use “team_uuid” “channel_uuid”):
        ```
        /create [“thread_title”] [“thread_message”] : create a new thread
        ```
      When team_uuid, channel_uuid and thread_uuid are defined (/use “team_uuid”“channel_uuid” “thread_uuid”):
        ```
        /create [“comment_body”] : create a new reply
        ```

    * ##### /List

      When the context is not defined (/use):
      ```
      /list : list all existing teams
      ```
      When team_uuid is defined (/use “team_uuid”):
      ```
      /list : list all existing channels
      ```
      When team_uuid and channel_uuid are defined (/use “team_uuid” “channel_uuid”):
      ```
      /list : list all existing threads
      ```
      When team_uuid, channel_uuid and thread_uuid are defined (/use “team_uuid” “channel_uuid” “thread_uuid”):
      ```
      /list : list all existing replies
      ```

    * ##### /Info

      When the context is not defined (/use):
      ```
      /info : display currently logged user infos
      ```
      When team_uuid is defined (/use “team_uuid”):
      ```
      /info : display currently selected team infos
      ```
      When team_uuid and channel_uuid are defined (/use “team_uuid” “channel_uuid”):
      ```
      /info : display currently selected channel infos
      ```
      When team_uuid, channel_uuid and thread_uuid are defined (/use “team_uuid” “channel_uuid” “thread_uuid”):
      ```
      /info : display currently selected thread infos
      ```

  * ### Informations

    Please note that all arguments of the existing commands have to be quoted with double quotes. A missing quote is interpreted as an error.

## Tests

## Documentation

  * ### Doxygen

## Uninstalling MyTeams

  ```
  rm -rf MyTeams/
  ```

## Contributors

*
*
*

## License

  This project is released under the [Apache 2.0 License](LICENSE.txt).
