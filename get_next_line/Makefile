#Project name
NAME=libgetnextline.a
#Compiler
CC=cc
#Compiler flags
CC_FLAGS= -Wall -Werror -Wextra
#Includes
INCLUDES=./ft_printf.h
#Source files
SRC = get_next_line.c get_next_line_utils.c
#Object files
OBJ=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

norm:
	-@norminette

.PHONY: all clean fclean re norm