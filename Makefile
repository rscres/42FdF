#Program name
NAME = fdf

#Compiler
CC = cc

#Compiler flags
CC_FLAGS = -Wall -Werror -Wextra -g3

#Source files
SRC = 	./src/main.c		\
		./src/read_map.c	\
		./src/draw_line.c	\
		./src/draw_line_utils.c\
		./src/lst_utils.c	\
		./src/plot_grid.c	\
		./src/draw.c		\
		./src/grid_to_iso.c	\
		./src/color.c		\
		./src/utils.c

#Source directory


#Object files
OBJ = $(SRC:.c=.o)

#Libraries
LIBS = -lmlx -Llibft -lft -lXext -lX11 -lm -lz

#Libft
LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CC_FLAGS) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CC_FLAGS) -I. -I./includes/ -O3 -c $< -o $@

$(LIBFT):
	@make -C libft 

clean:
	rm -rf $(OBJ)
	@make -C libft clean

fclean: clean
	rm -rf $(NAME)
	@make -C libft fclean

re: fclean all