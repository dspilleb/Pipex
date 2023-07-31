NAME =pipex

SRC = pipex.c commands.c files.c

LIBFT_A = libft.a
LIBFT_DIR = ./My_Libft/
LIBFT  = $(addprefix $(LIBFT_DIR), $(LIBFT_A))

FLAGS = -Wall -Wextra -Werror
INCLUDE = -fsanitize=address

OBJ = *.o

GREEN='\033[32m'

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	@gcc $(FLAGS) $(OBJ) $(LIBFT) $(INCLUDE) -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

$(OBJ): $(SRC)
	@gcc $(FLAGS) -c $(SRC)

pipex_clean:
	@rm -rf $(OBJ)

clean:
	@rm -rf $(OBJ)
	@make -C $(LIBFT_DIR) clean

fclean: pipex_clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all