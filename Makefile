CC := gcc

NAME := lem_in

CFLAGS := -Wall -Wextra -Werror -g

INC_FLAGS := -I includes -I printf -I printf/libft

PRINTF_DIR := printf
PRINTF_LIB := $(PRINTF_DIR)/libftprintf.a

SRCS := get_next_line.c parsing.c main.c \
        utils.c libft.c connectivity.c bfs.c list.c

OBJS := $(SRCS:.c=.o)
OBJDIR := $(addprefix obj/, $(OBJS))

INCLUDES := includes/lem_in.h includes/get_next_line.h

RM := rm -f

all : $(NAME)

$(PRINTF_LIB):
	@printf "\033[34m[Compiling printf]\033[0m\n"
	@$(MAKE) -C $(PRINTF_DIR)

$(NAME): $(OBJDIR) $(PRINTF_LIB)
	@printf "\033[34m[Compiling lem_in]\033[0m\n"
	$(CC) $(OBJDIR) $(PRINTF_LIB) $(CFLAGS) $(INC_FLAGS) -o $(NAME)
	@printf "\033[32m[Done]\033[0m\n"

obj/%.o : src/%.c $(INCLUDES) Makefile
	@mkdir -p obj
	$(CC) -c $< $(INC_FLAGS) $(CFLAGS) -o $@

leak: all
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME)

clean :
	$(RM) $(OBJDIR)
	$(MAKE) clean -C $(PRINTF_DIR)

fclean : clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(PRINTF_DIR)

re : fclean all

.PHONY : all clean fclean re
.SILENT :