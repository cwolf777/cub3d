NAME = cub3d
CC = gcc
CFLAGS = -Werror -Wextra -Wall -I$(LIBMLX_DIR)/include/MLX42 -I$(LIBFT_DIR) -I./include
DEBUG_FLAGS = -Werror -Wextra -Wall -I$(LIBMLX_DIR)/include/MLX42 -I$(LIBFT_DIR) -I./include -fsanitize=address -g
LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBMLX_DIR = ./libs/mlx
LIBMLX = $(LIBMLX_DIR)/build/libmlx42.a
SRC_DIR = ./src
VPATH = $(SRC_DIR) $(SRC_DIR)/utils $(SRC_DIR)/validation $(SRC_DIR)/init $(SRC_DIR)/parse \
		$(SRC_DIR)/game $(SRC_DIR)/game/render $(SRC_DIR)/game/movement $(SRC_DIR)/game/draw

SRCS =	main.c init.c init_img.c \
		parse_cub3d.c parse_graphics.c parse_img.c parse_map.c parse_rgb.c \
		validate_cub3d.c validate_file_extension.c validate_rgb.c validate_grid.c \
		player_movement.c handle_keypress.c game_loop.c handle_close.c \
		ray_caster.c render.c render_wall.c \
		draw_3d.c draw_line.c draw_minimap.c draw_player.c draw.c \
		free.c error.c convert.c str_utils.c print.c utils.c ft_split2.c

OBJS_DIR = objects
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

# Colors
GREEN = \033[0;32m
CYAN = \033[0;36m
RESET = \033[0m

all: $(NAME)

$(NAME): $(LIBMLX) $(LIBFT) $(OBJS)
	@echo "$(CYAN)"
	@echo "	░█████╗░██╗░░░██╗██████╗░  ██████╗░██████╗░"
	@echo "	██╔══██╗██║░░░██║██╔══██╗  ╚════██╗██╔══██╗"
	@echo "	██║░░╚═╝██║░░░██║██████╦╝  ░█████╔╝██║░░██║"
	@echo "	██║░░██╗██║░░░██║██╔══██╗  ░╚═══██╗██║░░██║"
	@echo "	╚█████╔╝╚██████╔╝██████╦╝  ██████╔╝██████╔╝"
	@echo "	░╚════╝░░╚═════╝░╚═════╝░  ╚═════╝░╚═════╝░"
	@echo "$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft -L$(LIBMLX_DIR)/build -lmlx42 -lglfw -lm -pthread
	@echo "$(GREEN)Compilation complete!$(RESET)"

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@echo "Creating $(OBJS_DIR) directory"
	@mkdir -p $(OBJS_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(LIBMLX):
	git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX_DIR)
	cmake $(LIBMLX_DIR) -B$(LIBMLX_DIR)/build && cmake --build $(LIBMLX_DIR)/build 

debug: CFLAGS = $(DEBUG_FLAGS)
debug: re

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug