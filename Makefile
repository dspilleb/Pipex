NAME = pipex

SRC_C = pipex.c commands.c data.c utils.c execution.c
SRC_DIR = ./Normal/
SRC = $(addprefix $(SRC_DIR), $(SRC_C))

BONUS_SRC_C = pipex_bonus.c commands_bonus.c data_bonus.c utils_bonus.c execution_bonus.c
BONUS_DIR = ./Bonus/
BONUS_SRC = $(addprefix $(BONUS_DIR), $(BONUS_SRC_C)) GNL/get_next_line_bonus.c GNL/get_next_line_utils_bonus.c

LIBFT_A = libft.a
LIBFT_DIR = ./My_Libft/
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_A))

FLAGS = -Wall -Wextra -Werror
INCLUDE = #-fsanitize=address -g

OBJ = *.o

GREEN='\033[32m'
ORANGE='\033[0;33m'
NONE='\033[0m'
BLUE='\033[0;34m'
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
	@echo $(BLUE)"- cleaning PIPEX -"$(NONE)
	@rm -rf $(OBJ)

clean:
	@echo $(BLUE)"- cleaning PIPEX -"$(NONE)
	@rm -rf $(OBJ)
	@echo $(YELLOW)"- cleaning LIBFT -"$(NONE)
	@make -C $(LIBFT_DIR) clean

fclean: pipex_clean
	@rm -rf $(NAME)
	@echo $(YELLOW)"- cleaning LIBFT -"$(NONE)
	@make -C $(LIBFT_DIR) fclean

bonus: fclean
	@gcc $(FLAGS) -c $(BONUS_SRC)
	@make -C $(LIBFT_DIR)
	@gcc $(FLAGS) $(OBJ) $(LIBFT) $(INCLUDE) -o $(NAME)
	@echo $(BLUE)"- Compiled Bonus-"$(NONE)

re: fclean all