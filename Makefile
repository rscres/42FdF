#Program name
NAME = fdf

#Compiler
CC = cc

#Compiler flags
CC_FLAGS = -Wall -Werror -Wextra -g3

#Source files
SRC = 	main.c			\
		read_map.c		\
		draw_line.c		\
		linked_lst.c	\
		plot_grid.c		\
		draw.c

#Object files
OBJ = $(SRC:.c=.o)

#Libraries
LIBS = -lmlx -Lget_next_line -lgetnextline -Llibft -lft -L/usr/lib -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CC_FLAGS) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CC_FLAGS) -I. -I./includes/ -O3 -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all