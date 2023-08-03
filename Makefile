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
LIBS = -lmlx -Llibft -lft -Lft_printf -lftprintf -lXext -lX11 -lm -lz

#Libft
LIBFT = ./libft/libft.a

#Ft_printf
PRINTF = ./ft_printf/libftprintf.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CC_FLAGS) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CC_FLAGS) -I. -I./includes/ -O3 -c $< -o $@

$(LIBFT):
	@make -C libft

$(PRINTF):
	@make -C ft_printf

clean_all:
	rm -rf $(OBJ)
	@make -C libft clean
	@make -C ft_printf clean

clean_lib:
	@make -C libft cleansrc/draw_line.c

clean:
	rm -rf $(OBJ)

fclean_all: clean_all
	rm -rf $(NAME)
	@make -C libft fclean
	@make -C ft_printf fclean

fclean_lib: clean_libs
	@make -C libft fclean
	@make -C ft_printf fclean

fclean: clean
	rm -rf $(NAME)

re_all: fclean_all all

re: fclean all