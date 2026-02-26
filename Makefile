CC := gcc

NAME := lem_in

CFLAGS := -Wall -Wextra -Werror -O3 -g

INC_FLAGS := -I includes

SRCS := ft_itoa.c get_next_line.c parsing.c main.c\
		 utils.c libft.c\

OBJS := ${SRCS:.c=.o}

OBJDIR := $(addprefix obj/, $(OBJS))

INCLUDES := includes/lem_in.h includes/get_next_line.h

RM  := rm -f 

all : $(NAME)

$(NAME) : $(OBJDIR)
	echo "\x1b[34m $1[Compiling Lem_in]\x1b[0m"
	$(CC) $(MLX_FLAGS) $(INC_FLAGS) $(OBJDIR) $(CFLAGS) -o $(NAME)
	echo "\x1b[34m $1[Done]\x1b[0m"

obj/%.o : src/%.c $(INCLUDES) Makefile
	mkdir -p obj
	$(CC) -c $< $(INC_FLAGS) $(CFLAGS) -o $@

leak: all
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME)

clean :
	$(RM) $(OBJDIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re libft
.SILENT :