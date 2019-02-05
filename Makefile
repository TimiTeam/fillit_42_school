NAME = fillit

DIR_SRCS = ./src/

DIR_OBJ = ./obj/

SRCS = arrange.c extra.c fillit.c make_shapes.c map.c main.c helper.c ft_strsplit.c

OBJ = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	clang $(FLAGS) -c $(addprefix $(DIR_SRCS), $(SRCS))
	mkdir -p obj
	mv $(OBJ) $(DIR_OBJ)
	clang $(FLAGS) $(addprefix $(DIR_OBJ), $(OBJ)) -o $(NAME)

clean:
	/bin/rm -rf $(DIR_OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
