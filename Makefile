##
## EPITECH PROJECT, 2023
## myTeams
## File description:
## Makefile
##

CLIENT 			=	client/

SERVER			=	server/

all:
				make -C $(CLIENT)
				make -C $(SERVER)

clean:
				make clean -C $(CLIENT)
				make clean -C $(SERVER)

fclean:			clean
				make fclean -C $(CLIENT)
				make fclean -C $(SERVER)

tests_run:
				make tests_run -C $(CLIENT)
				make tests_run -C $(SERVER)

re:				fclean all

.PHONY:			all clean fclean re
