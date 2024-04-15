##
## EPITECH PROJECT, 2024
## myteams | server
## File description:
## Makefile
##

SRC =			src/main.c						\
\
				src/utils.c						\
				src/server_management.c			\
				src/server_client.c				\
				src/private_discussion.c		\
				src/teams.c						\
				src/fuck_le_coding_style.c		\
\
				src/commands/log_commands.c					\
				src/commands/misc_commands.c				\
				src/commands/user_commands.c				\
				src/commands/private_discussion_commands.c	\
				src/commands/create_command.c				\
				src/commands/use_command.c					\
				src/commands/subscribe_commands.c			\


OBJ =			$(SRC:.c=.o)

INC =			-I./include -I./../libs/myteams
LIB =			-luuid -L./../libs/myteams -lmyteams
RPATH = 		-Wl,-rpath,./libs/myteams

CFLAGS =		-W -Wall -Werror -Wextra $(INC) $(LIB) $(RPATH) \
				-std=c11 -D_GNU_SOURCE -g3

NAME =			myteams_server

RM =			rm -f

$(NAME):		$(OBJ)
				gcc -o $(NAME) $(OBJ) $(CFLAGS)
				mv $(NAME) ..

all:			$(NAME)

debug:			CFLAGS += -g3 -ggdb
debug:			re

clean:
				$(RM) $(OBJ)

fclean:			clean
				$(RM) ../$(NAME)
				find . -name "*.gcda" -delete -or -name "*.gcno" -delete
				find . -name "*.log" -delete

re: 			fclean all

.PHONY: 		all debug clean fclean re
