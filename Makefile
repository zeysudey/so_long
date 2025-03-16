NAME = so_long
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -rf

FT_PRINTF = ft_printf/libftprintf.a

SRC = get_next_line/get_next_line.c \
      get_next_line/get_next_line_utils.c \
      create_map.c \
      so_long_utils.c \
      main.c free.c objects_check.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(FT_PRINTF)
		$(CC) $(CFLAGS) $(OBJ) $(FT_PRINTF) -o $(NAME)

$(FT_PRINTF):
		make -C ft_printf

clean:
		make clean -C ft_printf
		$(RM) $(OBJ)

fclean: clean
		make fclean -C ft_printf
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
