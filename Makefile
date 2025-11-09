#Program name
NAME = fdf

#Bonus program name
BONUS_NAME = fdf_bonus

#Compiler
CC = cc

#Compiler flags
CC_FLAGS = -Wall -Werror -Wextra -g3

#Source files
SRC = 	./src/main.c		\
		./src/img.c			\
		./src/events.c		\
		./src/validation.c	\
		./src/read_map.c	\
		./src/utils.c		\
		./src/draw.c		\
		./src/color.c		\
		./src/transform.c	\
		./src/scale.c

#Object files
OBJ = $(SRC:.c=.o)

#Bonus files
BONUS = ./bonus/main_bonus.c		\
		./bonus/img_bonus.c			\
		./bonus/events_bonus.c		\
		./bonus/validation_bonus.c	\
		./bonus/read_map_bonus.c	\
		./bonus/utils_bonus.c		\
		./bonus/draw_bonus.c		\
		./bonus/color_bonus.c		\
		./bonus/transform_bonus.c	\
		./bonus/scale_bonus.c		\
		./bonus/move_bonus.c		\
		./bonus/background_bonus.c	\
		./bonus/rotate_bonus.c		\
		./bonus/zoom_bonus.c		\
		./bonus/draw_line_bonus.c

#Bonus object files
BONUS_OBJ = $(BONUS:.c=.o)

#Libraries
LIBS = -Lmlx -lmlx_Linux -Llibft -lft -Lft_printf -lftprintf -lXext -lX11 -lm -lz

#Libft
LIBFT = ./libft/libft.a

#Ft_printf
PRINTF = ./ft_printf/libftprintf.a

#MLX
MLX = ./mlx/libmlx_Linux.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(PRINTF) $(MLX)
	$(CC) $(CC_FLAGS) $(OBJ) $(LIBS) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT) $(PRINTF) $(MLX)
	$(CC) $(CC_FLAGS) $(BONUS_OBJ) $(LIBS) -o $(BONUS_NAME)

%.o: %.c
	$(CC) $(CC_FLAGS) -I. -I./includes/ -O3 -c $< -o $@

$(LIBFT):
	@make -C libft

$(PRINTF):
	@make -C ft_printf

$(MLX):
	@make -C mlx

clean:
	rm -rf $(OBJ)
	rm -rf $(BONUS_OBJ)
	@make -C libft clean
	@make -C ft_printf clean
	@make -C mlx clean

fclean: clean
	rm -rf $(BONUS_NAME)
	rm -rf $(NAME)
	@make -C libft fclean
	@make -C ft_printf fclean
	@make -C mlx clean

re: fclean all bonus

.PHONY: all clean fclean re
