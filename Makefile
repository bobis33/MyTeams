##
## EPITECH PROJECT, 2024
## myteams
## File description:
## Makefile
##

CLIENT = 		Client/

SERVER = 		Server/

all:
				@make -C $(CLIENT)
				@make -C $(SERVER)

clean:
				@make clean -C $(CLIENT)
				@make clean -C $(SERVER)

fclean:
				@make fclean -C $(CLIENT)
				@make fclean -C $(SERVER)

re: 			fclean all

.PHONY: 		all clean fclean re
