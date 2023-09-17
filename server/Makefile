##
## EPITECH PROJECT, 2023
## myTeams
## File description:
## Makefile
##


SRC_MAIN 		=	src/main.c

SRC_UTILS		=	src/utils/my_putstr.c

SRC				=	src/error/error.c						\
					src/network/ip.c						\
					src/network/port.c						\
					src/server/server.c						\
					src/network/socket.c

SRC_TEST		=	units_tests/test.c

OBJ 			=	$(SRC_MAIN:.c=.o)						\
					$(SRC_UTILS:.c=.o)						\
					$(SRC:.c=.o)

OBJ_TEST		=	$(SRC_UTILS:.c=.o) 						\
					$(SRC_TEST:.c=.o)						\
					$(SRC:.c=.o)


CFLAGS			=	-W -Wall -Wextra -I./include

FLAGS_DEBUG 	= 	-g3

FLAGS_TEST 		=	--coverage -lcriterion

NAME			=	myteams_server

NAME_TEST		= 	unit_tests

$(NAME):			$(OBJ)
					gcc -o $(NAME) $(OBJ) $(CFLAGS)

all:				$(NAME)

debug: 				CFLAGS += $(FLAGS_DEBUG)

debug:				$(OBJ)
					gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
					rm -rf $(OBJ)

clean_test:
					rm -rf $(OBJ_TEST)
					find . -name "*.gcda" -delete -or -name "*.gcno" -delete

fclean:				clean clean_test
					rm -rf $(NAME)
					rm -rf $(NAME_TEST)

tests_run:			CFLAGS += --coverage

tests_run: 			$(OBJ_TEST)
					gcc -o $(NAME_TEST) $(OBJ_TEST) $(CFLAGS) $(FLAGS_TEST)
					./unit_tests --verbose

re:					fclean all

.PHONY: 			all debug clean clean_test fclean tests_run re
