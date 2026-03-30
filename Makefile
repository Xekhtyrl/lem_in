CC := gcc

NAME := lem_in

CFLAGS := -Wall -Wextra -Werror -g


LIBFT_DIR = includes/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

INC_FLAGS := -I includes -I $(LIBFT_DIR)/headers

SRCS := parsing.c main.c \
        utils.c connectivity.c bfs.c list.c \
		algo.c

SRC_DIR = src/
OBJ_DIR = obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))


RM := rm -f

all : $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT_LIB) $(OBJS)
	@printf "\033[34m[Compiling lem_in]\033[0m\n"
	$(CC) $(OBJS) $(CFLAGS) $(INC_FLAGS) $(LIBFT_LIB) -o $(NAME)
	@printf "\033[32m[Done]\033[0m\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< $(INC_FLAGS) -o $@

leak: all
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME)

clean :
	$(RM) -r $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR) 


fclean : clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR) 

re : fclean all

.PHONY : all clean fclean re
.SILENT :