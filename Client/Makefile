##
## EPITECH PROJECT, 2024
## myteams | client
## File description:
## Makefile
##

SRC =           src/main.c         \
                src/parse_args.c   \
                src/client.c       \

OBJ =			$(SRC:.c=.o)

INC =			-I./include -I./../libs/myteams
LIB =			-luuid -L./../libs/myteams -lmyteams
RPATH = 		-Wl,-rpath,./libs/myteams

CFLAGS =		-W -Wall -Werror -Wextra $(INC) $(LIB) $(RPATH) \
				-std=c11 -D_GNU_SOURCE

NAME =			myteams_cli

RM =			rm -f

$(NAME):		$(OBJ)
				gcc -o $(NAME) $(OBJ) $(CFLAGS)

all:			$(NAME)

debug:			CFLAGS += -g3 -ggdb
debug:			re

clean:
				$(RM) $(OBJ)

fclean:			clean
				$(RM) $(NAME)
				find . -name "*.gcda" -delete -or -name "*.gcno" -delete
				find . -name "*.log" -delete

re: 			fclean all

.PHONY: 		all debug clean fclean re
