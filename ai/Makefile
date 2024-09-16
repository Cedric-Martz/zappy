##
## EPITECH PROJECT, 2024
## B-YEP-400-STG-4-1-zappy-augustin.grosnon
## File description:
## Makefile
##

NUITKA = python3 -m nuitka
NUITKA_MODE = --standalone
SRC = main.py
BUILD_DIR = main.build
DIST_DIR = main.dist
BIN = zappy_ai

GREEN = \033[0;32m
YELLOW = \033[1;33m
RED = \033[0;31m
NC = \033[0m

all: setup_scripts

compiled: setup_compiled_scripts copy_config

$(DIST_DIR)/$(BIN): $(SRC)
	@printf "$(YELLOW)Compiling with Nuitka...$(NC)\n"
	@$(NUITKA) $(NUITKA_MODE) $(SRC) -o $(BIN)
	@if [ ! -f $(DIST_DIR)/$(BIN) ]; then \
		printf "$(RED)Compilation failed!$(NC)\n"; \
		exit 1; \
	fi

setup_scripts:
	@printf "$(GREEN)Setting up interpreted scripts$(NC)\n"
	@touch ../$(BIN) && printf '#!/bin/bash\n\npython3 ./ai/main.py $$@\n' > ../$(BIN) && chmod +x ../$(BIN)
	@cp -r logs ..
	@cp -r wordlist ..

setup_compiled_scripts:	$(DIST_DIR)/$(BIN)
	@printf "$(GREEN)Setting up compiled scripts$(NC)\n"
	@touch ../$(BIN) && printf '#!/bin/bash\n\n./ai/main.dist/$(BIN) $$@\n' > ../$(BIN) && chmod +x ../$(BIN)

copy_config:
	@printf "$(GREEN)Copying configuration files$(NC)\n"
	@cp -r config main.dist

clean:
	@printf "$(YELLOW)Cleaning build directories and logs$(NC)\n"
	@rm -rf $(BUILD_DIR)
	@rm -f *.log
	@rm -f logs/*.log

fclean: clean
	@printf "$(YELLOW)Performing full clean$(NC)\n"
	@rm -rf $(DIST_DIR)
	@find . -type d -name '__pycache__' -exec rm -rf {} +
	@rm -f ../$(BIN)
	@rm -rf ../logs
	@rm -rf ../wordlist

re: fclean all

.PHONY: all compiled clean fclean re setup_scripts setup_compiled_scripts copy_config
