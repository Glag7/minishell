NAME = libft.a
COMP = cc 
CFLAGS = -Wall -Wextra -Werror

SRC = src/
OBJ = obj/
HDR = hdr/

#DIRS
ARR = arr/
CHAR = char/
DLST = dlst/
FILE = file/
LST = lst/
MATH = math/
MEM = mem/
PRINT = print/
STR = str/
TSTR = tstr/

#SRCS
SRC_ARR = $(addprefix $(ARR), \
	  ft_chrarr_int.c \
	  ft_chrarr_len.c \
	  ft_chrarr_long.c \
	  ft_chrarr_ptr.c \
	  ft_freearr.c \
	  ft_freenarr.c \
	  ft_delarr.c \
	  ft_delnarr.c \
	  ft_sortint.c \
	  ft_sortlen.c \
	  ft_sortlong.c \
	  ft_sortptr.c \
	  ft_swapint.c \
	  ft_swaplen.c \
	  ft_swaplong.c \
	  ft_swapptr.c )
SRC_CHAR = $(addprefix $(CHAR), \
	   ft_is.c \
	   ft_tolower.c \
	   ft_toupper.c )
SRC_DLST = $(addprefix $(DLST), \
	   ft_dlstnew.c \
	   ft_dlstremove.c \
	   ft_dlstadd_back.c \
	   ft_dlstadd_front.c \
	   ft_dlstclear.c \
	   ft_dlstswap.c)
SRC_FILE = $(addprefix $(FILE), \
	   ft_gnl_tstr.c \
	   ft_gnl.c )
SRC_LST = $(addprefix $(LST), \
	  ft_lstat.c \
	  ft_lstlast.c \
	  ft_lstmap.c \
	  ft_lstnew.c \
	  ft_lsttstr_to_tstr.c \
	  ft_lstsize.c \
	  ft_lstadd_back.c \
	  ft_lstadd_front.c \
	  ft_lstclear.c \
	  ft_lstdelone.c \
	  ft_lstinsert.c \
	  ft_lstiter.c \
	  ft_lstpop.c \
	  ft_lsttstr_to_str.c )
SRC_MATH = $(addprefix $(MATH), \
	   ft_max.c \
	   ft_min.c \
	   ft_powi.c \
	   ft_sqrti.c )
SRC_MEM = $(addprefix $(MEM), \
	  ft_bzero.c \
	  ft_calloc.c \
	  ft_memchr.c \
	  ft_memcpy.c \
	  ft_memmove.c \
	  ft_memset.c \
	  ft_memcmp.c )
SRC_PRINT = $(addprefix $(PRINT), \
	    ft_printmem_fd.c \
	    ft_putendl_fd.c \
	    ft_putnbr_fd.c \
	    ft_putnbrbase_fd.c \
	    ft_putstr_fd.c)
SRC_STR = $(addprefix $(STR), \
	  ft_atoi.c \
	  ft_atoibase.c \
	  ft_in.c \
	  ft_strlcat.c \
	  ft_strlcpy.c \
	  ft_strlen.c \
	  ft_striteri.c \
	  ft_split.c \
	  ft_split_set.c \
	  ft_itoa.c \
	  ft_itoabase.c \
	  ft_strchr.c \
	  ft_strdup.c \
	  ft_strjoin.c \
	  ft_strmapi.c \
	  ft_strtrim.c \
	  ft_strnstr.c \
	  ft_strrchr.c \
	  ft_substr.c \
	  ft_strncmp.c )
SRC_TSTR = $(addprefix $(TSTR), \
	   ft_tstr_to_lst.c \
	   ft_iseol.c \
	   ft_tstr_dupstr.c \
	   ft_tstrnew.c \
	   ft_tstrdel.c \
	   ft_tstrfree.c )

#OBJS
OBJ_ARR = $(SRC_ARR:.c=.o)
OBJ_CHAR = $(SRC_CHAR:.c=.o)
OBJ_DLST = $(SRC_DLST:.c=.o)
OBJ_FILE = $(SRC_FILE:.c=.o)
OBJ_LST = $(SRC_LST:.c=.o)
OBJ_MATH = $(SRC_MATH:.c=.o)
OBJ_MEM = $(SRC_MEM:.c=.o)
OBJ_PRINT = $(SRC_PRINT:.c=.o)
OBJ_STR = $(SRC_STR:.c=.o)
OBJ_TSTR = $(SRC_TSTR:.c=.o)



#rules
all : $(NAME)
std : arr file lst mem str tstr

#folders rules
$(OBJ) :
	@ mkdir -p $(OBJ)
$(ARR) $(CHAR) $(DLST) $(FILE) $(LST) $(MATH) $(MEM) $(PRINT) $(STR) $(TSTR): $(OBJ)
	@ mkdir -p $(OBJ)$@

$(NAME) : arr char dlst file lst math mem print str tstr

$(OBJ)%.o: $(SRC)%.c
	@ $(COMP) $(CFLAGS) -c $^ -o $@ -I $(HDR) -D __FT_$(shell echo $(notdir $(patsubst %/, %, $(dir $@))) | tr '[:lower:]' '[:upper:]')__
	@ ar rcs $(NAME) $@

#folders
$(ARR:/=) : $(ARR) mem $(addprefix $(OBJ), $(OBJ_ARR))
	@ echo "compiling $@..."
$(CHAR:/=) : $(CHAR) $(addprefix $(OBJ), $(OBJ_CHAR))
	@ echo "compiling $@..."
$(DLST:/=) : $(DLST) mem $(addprefix $(OBJ), $(OBJ_DLST))
	@ echo "compiling $@..."
$(FILE:/=) : $(FILE) lst tstr $(addprefix $(OBJ), $(OBJ_FILE))
	@ echo "compiling $@..."
$(LST:/=) : $(LST) mem $(addprefix $(OBJ), $(OBJ_LST))
	@ echo "compiling $@..."
$(MATH:/=) : $(MATH) $(addprefix $(OBJ), $(OBJ_MATH))
	@ echo "compiling $@..."
$(MEM:/=) : $(MEM) $(addprefix $(OBJ), $(OBJ_MEM))
	@ echo "compiling $@..."
$(PRINT:/=) : $(PRINT) mem lst arr char $(addprefix $(OBJ), $(OBJ_PRINT))
	@ echo "compiling $@..."
$(STR:/=) : $(STR) mem lst arr $(addprefix $(OBJ), $(OBJ_STR))
	@ echo "compiling $@..."
$(TSTR:/=) : $(TSTR) mem lst str $(addprefix $(OBJ), $(OBJ_TSTR))
	@ echo "compiling $@..."

#cleaning
clean : 
	@ rm -rf obj/
fclean : clean
	@ rm -f $(NAME)
re : fclean all

#chokbar
chokbar :
	@ echo "                      ⢀⣤⠴⠶⠶⢤⣀⡀\n                    ⣀⠞⠁      ⠻⣄⡀         ⢀⠤⢄⣄⡀  ⣀⣴\n              ⣠⣾⠿⠴⠚⠋⠡⠈      ⡐⢑⠂⠙⠛⠲⣄⡀      ⣧⢵⠁   ⠷⠛\n     ⣾⣿      ⢈⠛⠁   ⢐⡊  ⢀⡐⠂         ⠙⠦⣀⡀   ⠈⠋\n    ⣸⡿⡾     ⡾    ⠨⡀⡜⣣⣜⡣⢔⡑⠠⢀⡀    ⠠⠊    ⢻⡀\n   ⢀⣿⣿⣟⡀⡀⡀⣀⠼⠨⢄⢀⡀⢀⡄⣁⢽⣿⣿⡿⠻⠙⠣⠪⢜⡌⡀⡀⢂⢤⢆⡀⡀⠠⡄⡑⠳⣀⡀⡀\n   ⠈⣿⣿⣿⡇⠛⠁    ⠑⠲⠕⠊⠉⠑⢿⡋      ⠘⢱⡣⠈⠉⠉⠑⠺⠇     ⠙⣄⡀\n    ⠋⠉⢠⠁      ⡨     ⡱⡀       ⢜⡃     ⢨⡀      ⣦⡀\n      ⣿⡌⠄⡀⡀⡀⡀⡜⢣⡀⡀⡀⡀⠨⢅⢱⠄⡀⡀⡀⡀⠠⠢⡆⡪⡀⢠⠳⢦⠤⣐⣒⣀⡀⡀⡀⡀⢌⢼⡀\n      ⣷⣮⡂⢠⠬⢡⡌⣿⣯⢜⡢⢢⢅⣨⣽⣷⣕⡲⢕⡡⢌⣑⣸⣿⣿⡦⣼⣒⠇⠨⡕⢢⣝⡁⢨⡅⢕⣺⣼⢉⣧\n      ⠸⣿⣿⣿⣯⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣽⣯⣷⣿⣿⣿⣿⡇⢕⡑⡘⡕⢪⢿⣾⣾⣿⣾⣯⠇⠎⣻\n     ⣀⣤⠉⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢼⣿⡇⡸⢷⣗⣿⣿⣿⣿⣿⡟⡲⢼⣯⡄\n   ⠈⣿⢿⣑⡄  ⠙⠿⣿⣿⣿⣿⣿⣿⠿⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡾⣽⣯⣽⣿⣼⣿⡿⠋⣠⣟⣿⣿⣯⡏\n    ⠘⣧⡵⡾     ⠉⡍⡉⣿⣿⡀⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣽⣽⠋⠉⢉⣤⣴⣿⣿⣿⣿⣿⡟\n     ⠹⡎⣁⣤⣄    ⠙⠛⠉⠈⢠⢟⡏⡟⡟⡯⢜⠉⢟⢋⠛⡋⠋⠏⢻⢸⡀  ⠘⠛⠿⣿⣿⣿⠋\n      ⠿⠻⣿⣷⣷⡀      ⠈⠛⠛⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠟⠋\n        ⢻⣿⣿⠟     ⢠⣶⣠⣄⢼⠿⡿⢿⣿⣿⣿⣿⣿⣿⢂⣿⣧⣾⣧⢀⡀\n         ⠉   ⢀⣿⣿⣷⣿⣿⣿⣿⣿⣿⣾⣷⣩⢭⣧⣦⠧⢝⡢⡙⢿⠿⣿⣿⣿⣿⣀⣦⡀\n         ⣴⢿⣿⣿⣯⣿⣆⠐⣾⣿⣾⣾⣽⣧⣍⠛⡶⣮⣬⡴⡳⢯⣟⣯⣽⣿⢞⢩⡹⢦⣮⠏\n         ⠈⢧⠹⣽⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣵⡑⢳⡿⣟⣾⡿⡿⢿⢎⣼⣿⣿⣇⡿\n           ⠻⣷⣮⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣸⡧⡕⢳⡻⡇⡸⣿⢟⡽⢿⣿⠁\n            ⠈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⣿⣿⡣⡸⡕⡳⡗⢝⡣⣿⣽⡯⣺⢿\n           ⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣻⣻⣿⣿⣵⢞⡳⡎⢝⢣⡯⣫⣝⣿⣿\n          ⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣼⣿⣇⣄⡗⣿⣿⣿⡽⡳⡺⢳⣪⢃⣇⣈⢻⡏\n         ⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⣿⣿⣿⣿⣿⣿⣿⣿⣟⣗⡧⢮⣳⡸⣿⣿⢨⣇\n        ⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠘⣿⣿⣿⣿⣿⣿⣿⣿⣷⡧⣺⢷⢧⣿⢟⢜⢿\n       ⣠⢿⣯⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣽⢯⡮⢷⣿⢮⢮⣷\n       ⣷⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢷⣕⡗⡮⣯⣳⣻⡻⡆\n       ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣾⣵⣿⣺⣗⣿\n       ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⡱⢮⢵⣜⢴⣙⣯⣾\n       ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣟⣾⣿⣟⣿⣽⣽⣿⣿⢵⢿\n       ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿ ⣿⣿⣿⣿⣿⣿⣿⣯⣿⡿⣿⣿⣿⣽⣟⢾⣏⢻⣿ ⣸⡀  ⣴⡀\n       ⣿⣿⣿⣿⣿⣿⣿⠇⣿⣿⣿⣿⣿⢰ ⣿⣿⣿⣿⣿⣿⣿⣿⣽⣿⣿⣿⣿⣿⣿⣾⣿⣷⣿⡴⠋⡌ ⣼⢣\n        ⠛⣿⣿⣿⣿⡟⠂⢹⣿⣿⣿⣿⠹⡀⠈⠻⣿⣿⣿⣿⣻⣾⣿⣿⣿⣿⣿⣿⣯⢿⣿⣿⢸ ⢀⣤⡿⢇⠇\n         ⢹⣿⣿⣿⢸⡀ ⣿⣿⣿⣿⣷⣑⡀  ⢿⣿⣿⣕⢻⣿⣿⣕⡿⡿⡧⡧⠌⣿⠟⣾⡚⢽⡞⢸⡟\n         ⠈⣿⣿⣿⣇⣷⡀     ⢻⣿⣿⣿⣿⣿⣿⣿⣷⢦⡮⣽⣽⣺⣮⣮⣮⡮⣽⠇⢇⣸⡷⠋\n           ⠋⢻⣿⣎⠶⣀⡀  ⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⣿⣷⣟⣿⣿⡿⠻⠛⠉\n             ⢿⣿⣿⣿⣿⡛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣯⣿⣽⡿⣽\n              ⢿⣿⠿⢿⣿⣦⠙⣿⣿⣿⣿⣻⣿⣿⣿⣿⣿⡿⣾⣿⣟⡿⡾\n                  ⠙⣿⠿⣦⠛⣿⣿⠛⢿⣿⣿⣿⣟⣿⠟⣠⡿⡼\n                     ⠈⢿⣦⠻⣿⣷⣤⣉⣉⣉⣤⣾⡿⡞\n                       ⠈⢿⣦⡉⠿⡿⡿⡿⠟⣡⠟\n                         ⠉⠿⣿⣿⣷⣾⠟⠁"

.PHONY: all std fclean clean re chokbar $(ARR:/=) $(CHAR:/=) $(DLST:/=) $(FILE:/=) $(LST:/=) $(MATH:/=) $(MEM:/=) $(PRINT:/=) $(STR:/=) $(TSTR:/=)
