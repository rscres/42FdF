/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:46:30 by renato            #+#    #+#             */
/*   Updated: 2023/08/07 19:39:20 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h> //remove
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "color.h"
# include "keys.h"

//Window dimensions definition
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

//STRUCTS
//MLX required info structs: img and win
typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_win;

//Vector coordinate structs: int and float versions
typedef struct s_point {
	int		x;
	int		y;
	int		z;
}	t_point;

typedef struct s_v3df {
	float	x;
	float	y;
	float	z;
}	t_v3df;

//Map struct containing basic map info
typedef struct s_map {
	int		height;
	int		width;
	int		max_z;
	int		min_z;
}	t_map;

//Draw info struct contains info neededd to draw each line
typedef struct s_draw_info {
	float	intersect;
	float	col_step;
	float	slope;
	int		steep;
	int		x1;
	int		x2;
	int		color;
	t_point	delta;
}	t_draw_info;

//Matrix struct contains each map point info
typedef struct s_matrix {
	t_point				points;
	int					x;
	int					y;
	int					z;
	unsigned int		color;
}	t_matrix;

//Camera struct contains the info for the 
typedef struct s_camera {
	float	zoom;
	int		offset_x;
	int		offset_y;
	int		rotation;
	int		projection;
}	t_camera;

//Master struct to nest other structs
typedef struct s_master {
	t_matrix	**matrix;
	t_win		win;
	t_img		mlx_img;
	t_map		map;
	t_camera	camera;
}	t_master;

//Event enum
enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

//FUNCTIONS
//main.c
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);

//events.c
int				handle_key_input(int key, t_win *win);
int				on_close(t_win *win);
int				handle_no_event(void);

//img.c
void			init_img(t_win *win, t_img *mlx_img, char *argv);
void			img_loop(t_win *win, t_master master);
void			destroy_win(t_master *master);

//validation.c
void			input_validation(char **argv, int argc);

//read_map.c
int				read_map(t_master *master, char *map_file);

//utils.c
unsigned int	ft_atox(char *hex);
void			clear_array(t_matrix **matrix, t_map map);

//draw.c
int				draw(t_master *master);

//color.c
void			set_color(t_matrix **matrix, t_map map);

#endif // FDF_H