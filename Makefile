NAME = minishell
LIB = libft/libft.a

COMP = clang
CFLAGS = -Wall -Wextra -gdwarf-4#-Werror

SRC_DIR = src/
OBJ_DIR = obj/
HDR_DIR = hdr/

PARSING = parsing/

SRC = main.c \
      $(PARSING)parse_quotes.c \
      $(PARSING)parse_pars.c \
      $(PARSING)check_pars.c \
      $(PARSING)parse_op.c \
      $(PARSING)check_op.c \
      $(PARSING)parse_hdoc.c \
      $(PARSING)add_hdoc.c \
      $(PARSING)parse_var.c \
      $(PARSING)parse_wdcard.c \
      $(PARSING)parse_redir.c \
      $(PARSING)check_redir.c \
      $(PARSING)free_lbuild.c \
      output.c

OBJ = $(SRC:.c=.o)

all : $(NAME)
	echo no push

bonus : all

$(LIB) :
	@ make -C libft/ char lst tstr math

$(OBJ_DIR) :
	@ mkdir -p $(OBJ_DIR)

$(OBJ_DIR)$(PARSING) : $(OBJ_DIR)
	@ mkdir -p $(OBJ_DIR)$(PARSING)

$(NAME) : $(LIB) $(OBJ_DIR)$(PARSING) $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJ))
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
