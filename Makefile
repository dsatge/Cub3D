NAME = cub3D

C_FILES = main.c\
			init.c\
			input.c\
			utils.c\
			read_map.c\
			init_utils.c\
			garbage/garbage.c\
			parsing/parsing.c\
			parsing/flood_fill.c\
			parsing/parsing_bis.c\
			parsing/name_texture.c\
			parsing/utils_parsing.c\
			parsing/flood_fill_utils.c\
			parsing/parsing_size_map.c\
			garbage/garbage_utils.c\
			parsing/parsing_colors_utils.c\
			display/floor_ceiling.c\
			display/minimap.c\
			display/map_formated.c\
			display/map_formated_utils.c\
			display/colours.c\
			display/click.c\
			display/ray_casting.c\
			display/click_utils.c\
			display/move_player.c\
			display/ray_casting_utils.c\
			display/dda.c\


UNAME_S = $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	MLX = lib/mlx_mac
	MLX_LIB = $(MLX)/libmlx.a
	MLXFLAG = -L$(MLX) -lmlx -framework OpenGL -framework AppKit
else ifeq ($(UNAME_S), Linux)
	MLX = lib/mlx_linux
	MLX_LIB = $(MLX)/libmlx.a
	MLXFLAG = -L$(MLX) -lmlx -lXext -lX11 -lm -lz
else
	$(error OS non supporte : $(UNAME_S). Utilisez macOS ou Linux / WSL.)
endif

LIBFT = lib/libft/libft.a
PRINTF = lib/ft_printf/libftprintf.a

SRCS = $(addprefix srcs/,$(C_FILES))
OBJS = $(SRCS:.c=.o)

# -I $(MLX) au lieu de $(MLX) tout seul
CFLAGS = -Wall -Werror -Wextra -I includes/ -I $(MLX) -g

all: ${NAME}

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

${NAME}: ${OBJS}
	@make -C ${MLX} > /dev/null 2>&1
	@make -C lib/libft
	@make -C lib/ft_printf
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) $(MLXFLAG) -o $(NAME)

bonus: ${OBJS}
	@make -C ${MLX} > /dev/null 2>&1
	@make -C lib/libft
	@make -C lib/ft_printf
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) $(MLXFLAG) -o $(NAME) -D BONUS=1

clean:
	rm -f $(OBJS)
	@make -C ${MLX} clean > /dev/null 2>&1 || true
	@make -C lib/libft clean
	@make -C lib/ft_printf clean

fclean: clean
	rm -rf ${NAME}
	@make -C lib/libft fclean
	@make -C lib/ft_printf fclean

re: fclean all

.PHONY: all clean fclean re bonus