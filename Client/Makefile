##
## EPITECH PROJECT, 2024
## myteams | client
## File description:
## Makefile
##

SRC =           src/main.c         				\
                src/parse_args.c   				\
                src/client.c       				\
				src/commands/help.c				\
				src/commands/login.c			\
				src/commands/user.c				\
				src/commands/send.c				\
				src/commands/messages.c			\
				src/commands/create.c			\
				src/commands/use.c				\
				src/commands/subscribe.c		\
				src/commands/unsubscribe.c		\
				src/commands/subscribed.c		\

OBJ =			$(SRC:.c=.o)

INC =			-I./include -I./../libs/myteams
LIB =			-luuid -L./../libs/myteams -lmyteams

CFLAGS =		-W -Wall -Wextra $(INC) $(LIB) -std=c11 -D_GNU_SOURCE

NAME =			myteams_cli

RM =			rm -f

$(NAME):		$(OBJ)
				gcc -o $(NAME) $(OBJ) $(CFLAGS)
				mv $(NAME) ../

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
