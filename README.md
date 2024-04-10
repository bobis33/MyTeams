# EPITECH | B-NWP-400 | MyTeams

![Epitech](doc/png/Epitech_banner.png)

## Description

The goal of this project is to create a server and a CLI client. 


## Requirements

- [GNU C Library](https://www.gnu.org/software/libc/)
- [Libuuid](https://linux.die.net/man/3/libuuid)


## Server

The server is able to handle several clients.

When the server shutdown it save internal information.
When the server start it look if the save exist and load it.

The server will print every requested events on the standard error output.
In specific case some information can be displayed on the standard output.

There is no password authentication required.

* ### Usage

```bash
$> ./Server/myteams_server [port]
```


## CLI Client

* ### Usage

```bash
$> ./Client/myteams_client [ip] [port]
```

* ### Features

  show help
    ```shell
      /help
    ```

  set the user_name used by client
    ```shell
      /login ["user_name"]
    ```

  disconnect the client from the server
    ```shell
      /logout
    ```

  get the list of all users that exist on the domain
    ```shell
      /users
    ```

  get information about a user
    ```shell
      /user ["user_uuid"]
    ```

  send a message to a user
    ```shell
    /send ["user_uuid"] ["message_body"]
    ```

  list all messages exchange with a user
    ```shell
    /messages ["user_uuid"]
    ```

  subscribe to the event of a team and its subdirectories (enable reception of all events from a team)
    ```shell
    /subscribe ["team_uuid"]
    ```

  list all subscribed teams or list all users subscribed to a team
    ```shell
    /subscribed ?["team_uuid"]
    ```

  unsubscribe from a team
    ```shell
    /unsubscribe ["team_uuid"]
    ```

  use specify a context team/channel/thread
    ```shell
    /use ?["team_uuid"] ?["channel_uuid"] ?["thread_uuid"] 
    ```

  based on what is being used create the sub resource
    ```shell
    /create
    ```

  based on what is being used list all the sub resources
    ```shell
    /list
    ```

  based on what is being used list the current
    ```shell
    /info
    ```

    * #### /Create
        When the context is not defined (/use):
        ```shell
          /create ["team_name"] ["team_description"] : create a new team
        ```
      
        When team_uuid is defined (/use "team_uuid"):
        ```shell
          /create ["channel_name"] ["channel_description"] : create a new channel
        ```
      
        When team_uuid and channel_uuid are defined (/use "team_uuid" "channel_uuid"):
        ```shell
          /create ["thread_title"] ["thread_message"] : create a new thread
        ```
      
        When team_uuid, channel_uuid and thread_uuid are defined (/use "team_uuid" "channel_uuid" "thread_uuid"):
        ```shell
          /create ["comment_body"] : create a new reply
        ```

    * #### /List

      When the context is not defined (/use):
      ```shell
      /list : list all existing teams
      ```
      
      When team_uuid is defined (/use “team_uuid”):
      ```shell
      /list : list all existing channels
      ```
      
      When team_uuid and channel_uuid are defined (/use “team_uuid” “channel_uuid”):
      ```shell
      /list : list all existing threads
      ```
      
      When team_uuid, channel_uuid and thread_uuid are defined (/use “team_uuid” “channel_uuid” “thread_uuid”):
      ```shell
      /list : list all existing replies
      ```

    * #### /Info

      When the context is not defined (/use):
      ```shell
      /info : display currently logged user infos
      ```
      
      When team_uuid is defined (/use “team_uuid”):
      ```shell
      /info : display currently selected team infos
      ```
      
      When team_uuid and channel_uuid are defined (/use “team_uuid” “channel_uuid”):
      ```shell
      /info : display currently selected channel infos
      ```
      
      When team_uuid, channel_uuid and thread_uuid are defined (/use “team_uuid” “channel_uuid” “thread_uuid”):
      ```shell
      /info : display currently selected thread infos
      ```


* ### Information

  Please note that all arguments of the existing commands have to be quoted with double quotes. A missing quote is interpreted as an error.


## Commit Norms

| Commit Type | Description                                                                                                               |
|:------------|:--------------------------------------------------------------------------------------------------------------------------|
| build       | Changes that affect the build system or external dependencies (npm, make, etc.)                                           |
| ci          | Changes related to integration files and scripts or configuration (Travis, Ansible, BrowserStack, etc.)                   |
| feat        | Addition of a new feature                                                                                                 |
| fix         | Bug fix                                                                                                                   |
| perf        | Performance improvements                                                                                                  |
| refactor    | Modification that neither adds a new feature nor improves performance                                                     |
| style       | Change that does not affect functionality or semantics (indentation, formatting, adding space, renaming a variable, etc.) |
| docs        | Writing or updating documentation                                                                                         |
| test        | Addition or modification of tests                                                                                         |

