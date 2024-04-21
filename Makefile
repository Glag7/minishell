NAME = minishell
LIB = libft/libft.a

COMP = clang
CFLAGS = -Wall -Wextra -gdwarf-4#-Werror

SRC_DIR = src/
OBJ_DIR = obj/
HDR_DIR = hdr/

SRC = main.c \
      parse_quotes.c \
      parse_pars.c \
      check_pars.c \
      output.c

OBJ = $(SRC:.c=.o)

all : $(NAME)
	echo no push

bonus : all

$(LIB) :
	@ make -C libft/ char lst tstr

$(OBJ_DIR) :
	@ mkdir -p $(OBJ_DIR)

$(NAME) : $(LIB) $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJ))
	@ $(COMP) $(CFLAGS) $(addprefix $(OBJ_DIR), $(OBJ)) $(LIB) -o $@ -lreadline

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@ $(COMP) $(CFLAGS) -c $^ -o $@ -I $(HDR_DIR) -I libft/hdr

clean :
	@ rm -rf $(OBJ_DIR)
	@ make -C libft/ clean

fclean : clean
	@ rm -f $(NAME)
	@ rm -f $(LIB)

re : fclean all

.PHONY: all bonus fclean clean re
