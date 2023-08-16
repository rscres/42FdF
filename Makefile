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
BONUS = ./bonus/main_bonus			\
		./bonus/img_bonus			\
		./bonus/events_bonus		\
		./bonus/validation_bonus	\
		./bonus/read_map_bonus		\
		./bonus/utils_bonus			\
		./bonus/draw_bonus			\
		./bonus/color_bonus			\
		./bonus/transform_bonus		\
		./bonus/scale_bonus

#Bonus object files
BONUS_OBJ = $(BONUS:.c=.o)

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

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CC_FLAGS) $(BONUS_OBJ) $(LIBS) -o $(BONUS_NAME)

$(LIBFT):
	@make -C libft

$(PRINTF):
	@make -C ft_printf

clean_all:
	rm -rf $(OBJ)
	@make -C libft clean
	@make -C ft_printf clean

clean_lib:
	@make -C libft clean
	@make -C ft_printf clean

clean:
	rm -rf $(OBJ)

fclean_all: clean_all
	rm -rf $(NAME)
	@make -C libft fclean
	@make -C ft_printf fclean

fclean_lib: clean_lib
	@make -C libft fclean
	@make -C ft_printf fclean

fclean: clean
	rm -rf $(NAME)

re_all: fclean_all all

re: fclean all

.PHONY: all clean fclean re