NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iget_next_line  -Ift_printf -Iminilibx-linux

MLX_FLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

GNL_SRCS = get_next_line/get_next_line.c \
           get_next_line/get_next_line_utils.c
GNL_OBJS = $(GNL_SRCS:.c=.o)

SRCS = create_map.c fill_map.c handle_errors.c\
      so_long_utils.c init_mlx.c game.c move.c\
      main.c free.c checks.c\
	$(GNL_SRCS)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@


$(NAME): $(OBJS)
	@make -C ft_printf
	@make -C minilibx-linux
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) ft_printf/libftprintf.a $(MLX_FLAGS)

clean:
	@make -C ft_printf clean
	@make -C minilibx-linux clean
	@rm -f $(OBJS) $(GNL_OBJS)

fclean: clean
	@make -C ft_printf fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re