NAME = cub3d
CC = gcc
CFLAGS = -Werror -Wextra -Wall -I./include
DEBUG_FLAGS = -Werror -Wextra -Wall -I./include -fsanitize=address -g
SRC_DIR = ./src
VPATH = $(SRC_DIR)
SRCS =	main.c
OBJS_DIR = objects
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

# Colors
GREEN = \033[0;32m
CYAN = \033[0;36m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(CYAN)"
	@echo "	░█████╗░██╗░░░██╗██████╗░  ██████╗░██████╗░"
	@echo "	██╔══██╗██║░░░██║██╔══██╗  ╚════██╗██╔══██╗"
	@echo "	██║░░╚═╝██║░░░██║██████╦╝  ░█████╔╝██║░░██║"
	@echo "	██║░░██╗██║░░░██║██╔══██╗  ░╚═══██╗██║░░██║"
	@echo "	╚█████╔╝╚██████╔╝██████╦╝  ██████╔╝██████╔╝"
	@echo "	░╚════╝░░╚═════╝░╚═════╝░  ╚═════╝░╚═════╝░"
	@echo "$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Compilation complete!$(RESET)"

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@echo "Creating $(OBJS_DIR) directory"
	@mkdir -p $(OBJS_DIR)

debug: CFLAGS = $(DEBUG_FLAGS)
debug: re

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug