NAME = libft.a

C_GREEN = \033[0;32m
C_RED = \033[0;31m
C_BLUE = \033[0;34m
C_PURPLE = \033[1;35m
C_END= \033[0m

#__________ PATHWAY __________#

SRC_DIR = Sources/

ASCII_DIR =	ft_is_ascii/
LST_DIR = ft_list/
MEM_DIR = ft_mem_manip/
STR_DIR = ft_string_manip/
PUT_DIR = ft_write/
GNL_DIR = Get_Next_Line/
PRINTF_DIR = libftprintf/
OTH_DIR = others/
OBJ_DIR = obj/

HEADERS = ./headers

#__________ REGROUP __________#

ASCII_SRC = ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c

MEM_SRC =	ft_memset.c 	\
			ft_bzero.c 		\
			ft_memcpy.c 	\
			ft_memmove.c 	\
			ft_memcmp.c 	\
			ft_memchr.c 

STR_SRC = 	ft_strlcpy.c	ft_strlcat.c	\
			ft_toupper.c	ft_tolower.c	\
			ft_strchr.c		ft_strrchr.c	\
			ft_strncmp.c	ft_strnstr.c	\
			ft_strdup.c		ft_substr.c		\
			ft_strjoin.c	ft_strlen.c		\
			ft_strtrim.c	ft_split.c		\
			ft_strmapi.c	ft_striteri.c

PUT_SRC =	ft_putchar_fd.c	\
			ft_putstr_fd.c	\
			ft_putendl_fd.c	\
			ft_putnbr_fd.c

OTH_SRC =	ft_atoi.c	\
			ft_calloc.c	\
			ft_itoa.c

LST_SRC =	ft_lstnew.c			\
			ft_lstadd_front.c	\
			ft_lstsize.c		\
			ft_lstlast.c		\
			ft_lstadd_back.c	\
			ft_lstdelone.c		\
			ft_lstclear.c		\
			ft_lstiter.c		\
			ft_lstmap.c

PRINTF_SRC = ft_printf_utils.c	\
			ft_printf_utils2.c	\
			ft_printf.c

GNL_SRC = 	get_next_line.c		get_next_line_utils.c

MY_SOURCES =	$(addprefix $(ASCII_DIR), $(ASCII_SRC))	\
				$(addprefix $(MEM_DIR), $(MEM_SRC))		\
				$(addprefix $(STR_DIR), $(STR_SRC))		\
				$(addprefix $(PUT_DIR), $(PUT_SRC))		\
				$(addprefix $(OTH_DIR), $(OTH_SRC))		\
				$(addprefix $(LST_DIR), $(LST_SRC))		\
				$(addprefix $(PRINTF_DIR), $(PRINTF_SRC))	\
				$(addprefix $(GNL_DIR), $(GNL_SRC))
				
				
MY_OBJECTS = $(addprefix $(OBJ_DIR), $(MY_SOURCES:.c=.o))

CFLAGS = -Wall -Werror -Wextra

#___________ RULES ___________#

all: $(NAME)

$(NAME): $(MY_OBJECTS)
	@ar rc $(NAME) $(MY_OBJECTS)
	@printf "all files have been compiled with $(C_PURPLE) $(CFLAGS) $(C_END)\n"
	@printf "$(C_BLUE)libft.a created$(C_END)\n"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@gcc ${CFLAGS} -I $(HEADERS) -c $< -o $@

-include $(OBJS:.o=.d)

clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(C_RED)browser hystory cleared, you are safe now$(C_END)\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "$(C_RED)there is nothing to see here$(C_END)\n"

re: fclean all

.PHONY: all clean fclean re