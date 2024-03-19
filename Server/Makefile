##
## EPITECH PROJECT, 2024
## myteams | server
## File description:
## Makefile
##

SRC =           src/main.c

OBJ =           $(SRC:.c=.o)

INC =           -I./include

CFLAGS =		-W -Wall -Werror -Wextra $(INC) -std=c11 -D_GNU_SOURCE

NAME =          myteams_server

RM = 	        rm -f

$(NAME):        $(OBJ)
				gcc -o $(NAME) $(OBJ) $(CFLAGS)

all:            $(NAME)

debug:          CFLAGS += -g3 -ggdb
debug:          re

clean:
				$(RM) $(OBJ)

fclean:         clean
				$(RM) $(NAME)
				find . -name "*.gcda" -delete -or -name "*.gcno" -delete
				find . -name "*.log" -delete

re: 			fclean all

.PHONY: 		all debug clean fclean re
