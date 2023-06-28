#Program name
NAME = fdf
#Compiler
CC = cc
#Compiler flags
CC_FLAGS = -Wall -Werror -Wextra
#Source files
SRC = main.c
#Object files
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) $(CC_FLAGS) -I/usr/include -I./mlx_linux -O3 -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all