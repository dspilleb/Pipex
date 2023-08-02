NAME = pipex

SRC = pipex.c commands.c data.c utils.c execution.c

LIBFT_A = libft.a
LIBFT_DIR = ./My_Libft/
LIBFT  = $(addprefix $(LIBFT_DIR), $(LIBFT_A))

FLAGS = -Wall -Wextra -Werror
INCLUDE = #-fsanitize=address -g

OBJ = *.o

GREEN='\033[32m'
ORANGE='\033[0;33m'
NONE='\033[0m'
YELLOW='\033[1;33m'

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(ORANGE)"- Compiling LIBFT -"$(NONE)
	@make -C $(LIBFT_DIR)
	@gcc $(FLAGS) $(OBJ) $(LIBFT) $(INCLUDE) -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

$(OBJ): $(SRC)
	@gcc $(FLAGS) -c $(SRC)

pipex_clean:
	@rm -rf $(OBJ)

clean:
	@rm -rf $(OBJ)
	@echo $(YELLOW)"- cleaning LIBFT -"$(NONE)
	@make -C $(LIBFT_DIR) clean

fclean: pipex_clean
	@rm -rf $(NAME)
	@echo $(YELLOW)"- cleaning LIBFT -"$(NONE)
	@make -C $(LIBFT_DIR) fclean

re: fclean all