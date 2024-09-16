##
## EPITECH PROJECT, 2024
## B-YEP-400-STG-4-1-zappy-augustin.grosnon
## File description:
## Makefile
##

all: zappy_server zappy_gui zappy_ai

zappy_server:
	make -C ./server

zappy_gui:
	make -C ./gui

zappy_ai:
	make -C ./ai

clean:
	make clean -C ./server
	make clean -C ./gui
	make clean -C ./ai

fclean:
	make fclean -C ./server
	make fclean -C ./gui
	make fclean -C ./ai

re: fclean all

.PHONY: all clean fclean re zappy_server zappy_gui zappy_ai
