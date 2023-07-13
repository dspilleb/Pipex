NAME = pipex

SRC = pipex.c commands.c

LIBFT_A = libft.a
LIBFT_DIR = ./My_Libft/
LIBFT  = $(addprefix $(LIBFT_DIR), $(LIBFT_A))

FLAGS =
INCLUDE =

OBJ = *.o

NONE='\033[0m'
GREEN='\033[32m'
YELLOW='\033[33m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(CURSIVE)$(GRAY) "     - Making libft..." $(NONE)
	@make -C $(LIBFT_DIR)
	@echo $(CURSIVE)$(GRAY) "     - Compiling" $(NONE)
	@gcc $(FLAGS) $(OBJ) $(LIBFT) $(INCLUDE) -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

$(OBJ): $(SRC)
	@echo $(CURSIVE)$(GRAY) "     - Making object files..." $(NONE)
	@gcc $(FLAGS) -c $(SRC)

clean:
	@echo $(CURSIVE)$(GRAY) "     - Removing object files..." $(NONE)
	@rm -rf $(OBJ)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo $(CURSIVE)$(GRAY) "     - Removing" $(NONE)
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all