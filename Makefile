NAME = minishell
LIB = libft/libft.a

COMP = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src/
OBJ_DIR = obj/
HDR_DIR = hdr/

PARSING = parsing/
BUILTINS = builtins/
COMMON = common/
EXEC = exec/

SRC = main.c \
      $(PARSING)parse_quotes.c \
      $(PARSING)parse_pars.c \
      $(PARSING)parse_op.c \
      $(PARSING)check_op.c \
      $(PARSING)parse_hdoc.c \
      $(PARSING)add_hdoc.c \
      $(PARSING)parse_var.c \
      $(PARSING)parse_wdcard.c \
      $(PARSING)parse_redir.c \
      $(PARSING)check_redir.c \
      $(PARSING)maybe_del.c \
      \
      $(BUILTINS)builtins_utils.c \
      $(BUILTINS)cd.c \
      $(BUILTINS)cd_envp.c \
      $(BUILTINS)echo.c \
      $(BUILTINS)env.c \
      $(BUILTINS)exit.c \
      $(BUILTINS)export.c \
      $(BUILTINS)export_alloc_envp.c \
      $(BUILTINS)export_update_envp.c \
      $(BUILTINS)export_only.c \
      $(BUILTINS)pwd.c \
      $(BUILTINS)unset.c \
      $(BUILTINS)wrap.c \
      \
      $(COMMON)sig.c \
      $(COMMON)sig_handle.c \
      $(COMMON)init_mini.c \
      $(COMMON)wrap.c \
      $(COMMON)free_lst.c \
      $(COMMON)dup_envp.c \
      $(COMMON)dup_envp_shlvl.c \
      $(COMMON)output.c \
      \
      $(EXEC)execline.c \
      $(EXEC)fill_hdoc.c \
      $(EXEC)fill_file.c \
      $(EXEC)hdoc_replace.c \
      $(EXEC)varchr.c \
      $(EXEC)waitall.c \
      $(EXEC)update_pipes.c \
      $(EXEC)find_next_op.c \
      $(EXEC)exec_cmd.c \
      $(EXEC)parse_cmd.c \
      $(EXEC)get_redir.c \
      $(EXEC)get_fnames.c \
      $(EXEC)split_words.c \
      $(EXEC)add_word_str.c \
      $(EXEC)exp_wdcard.c \
      $(EXEC)do_cmd.c \
      $(EXEC)add_wdname.c \
      $(EXEC)get_cmd.c \
      $(EXEC)build_redirs.c \
      $(EXEC)open_redir.c \
      $(EXEC)get_path.c \
      $(EXEC)get_path_err.c \
      $(EXEC)parse_wdcard_again.c \

OBJ = $(SRC:.c=.o)

all : $(NAME)

bonus : all

stupid : $(LIB) $(OBJ_DIR)$(PARSING) $(OBJ_DIR)$(COMMON) $(OBJ_DIR)$(BUILTINS) $(OBJ_DIR)$(EXEC) $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJ))
	@ $(COMP) $(CFLAGS) -D STUPID_TESTER -c $(SRC_DIR)$(COMMON)init_mini.c -o $(OBJ_DIR)$(COMMON)init_mini.o -I $(HDR_DIR) -I libft/hdr
	@ $(COMP) $(CFLAGS) $(addprefix $(OBJ_DIR), $(OBJ)) $(LIB) -o $(NAME) -lreadline

$(LIB) :
	@ make -C libft/ char lst tstr math file print

$(OBJ_DIR) :
	@ mkdir -p $(OBJ_DIR)

$(OBJ_DIR)$(PARSING) : $(OBJ_DIR)
	@ mkdir -p $(OBJ_DIR)$(PARSING)

$(OBJ_DIR)$(BUILTINS) : $(OBJ_DIR)
	@ mkdir -p $(OBJ_DIR)$(BUILTINS)

$(OBJ_DIR)$(COMMON) : $(OBJ_DIR)
	@ mkdir -p $(OBJ_DIR)$(COMMON)

$(OBJ_DIR)$(EXEC) : $(OBJ_DIR)
	@ mkdir -p $(OBJ_DIR)$(EXEC)

$(NAME) : $(LIB) $(OBJ_DIR)$(PARSING) $(OBJ_DIR)$(COMMON) $(OBJ_DIR)$(BUILTINS) $(OBJ_DIR)$(EXEC) $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJ))
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

.PHONY: all bonus fclean clean re stupid
