##
## EPITECH PROJECT, 2024
## B-YEP-400-STG-4-1-zappy-augustin.grosnon
## File description:
## Makefile
##

SRC		=	src/main.c      \
			src/setup_server.c      \
			src/loop_server.c       \
			src/handle_server.c     \
			src/handle_time.c	\
			src/free_all.c  \
			src/commands/handle_commands.c  \
			src/commands/execute_commands.c  \
			src/commands/admin_commands.c	\
			src/commands/choose_type.c	\
			src/commands/help.c	\
			src/commands/gui/map_infos.c	\
			src/commands/gui/player_infos.c	\
			src/commands/gui/ressources_actions.c	\
			src/commands/gui/player_actions.c	\
			src/commands/gui/egg_infos.c	\
			src/commands/gui/time_infos.c	\
			src/commands/ai/ai_actions.c	\
			src/commands/ai/ai_infos.c	\
			src/commands/ai/eject_players.c	\
			src/commands/ai/move_player.c	\
			src/commands/debug/get_idx_ressources.c	\
			src/commands/debug/messages_commands.c	\
			src/commands/debug/player_commands.c	\
			src/commands/debug/server_commands.c	\
			src/commands/debug/settings_commands.c	\
			src/commands/debug/world_actions.c	\
			src/commands/debug/logger.c     \
			src/utils/calcul_utils.c     \
			src/utils/string_utils.c	\
			src/utils/tab_utils.c	\
			src/flags/handle_flags.c	\
			src/flags/get_flags.c	\
			src/flags/get_team_name.c	\
			src/flags/world_setup.c	\
			src/flags/place_ressources.c

OBJ	= $(patsubst src/%.c,build/%.o,$(SRC))
DIRS	=	$(sort $(dir $(OBJ)))

NAME		=       zappy_server

CFLAGS	=	-g -I./include
CFLAGS	+=	-Wall -Wextra

all: build $(NAME)

build:
	mkdir -p $(DIRS)

$(NAME): $(OBJ)
	g++ $^ -o $@ $(CFLAGS)
	mv $(NAME) ../$(NAME)

build/%.o:	src/%.c
	gcc -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ)
	rm -rf build

fclean: clean
	rm -f ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
