NAME		=	pipex
INCLUDE		=	include
CFLAGS		=	-Wall -Wextra -Werror -Iinclude
LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a

SRC			=	$(wildcard src/*.c)
OBJ			=	$(SRC:.c=.o)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)

%.o: %.c include/pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re