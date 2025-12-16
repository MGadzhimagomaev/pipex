NAME		=	pipex
INCLUDE		=	include
LIBFT		=	libft
SRC			=	$(wildcard src/*.c)
OBJ			=	$(SRC:.c=.o)

$(NAME):	$(OBJ)
			@make -C $(LIBFT)
			@cp libft/libft.a .
			@mv libft.a $(NAME)
			ar rcs $(NAME) $(OBJ)

.c.o:
	cc -Wall -Wextra -Werror -fsanitize=address -c $< -o $@

all:		$(NAME)

clean:
	rm -rf	$(OBJ)
	@make clean -C $(LIBFT)

fclean: clean
	rm -rf	$(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re