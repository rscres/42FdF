/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:46:30 by renato            #+#    #+#             */
/*   Updated: 2023/07/25 13:16:46 by rseelaen         ###   ########.fr       */
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
# include "color.h"
# include "keys.h"

//Window dimensions definition
# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 800

//STRUCTS
//MLX required info structs: img and win
typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_win;

//Vector coordinate structs: int and float versions
typedef struct s_point {
	int		x;
	int		y;
	int		z;
}				t_point;

typedef struct s_v3df {
	float	x;
	float	y;
	float	z;
}				t_v3df;

//Delta struct
typedef struct s_delta {
	float	x;
	float	y;
}				t_delta;

//Map struct containing basic map info
typedef struct s_map {
	int		height;
	int		width;
	int		max_z;
	int		min_z;
	float	offset_x;
	float	offset_y;
}				t_map;

//Draw info struct contains info neededd to draw each line
typedef struct s_draw_info {
	float	intersect;
	float	col_step;
	float	slope;
	int		steep;
	int		x1;
	int		x2;
	int		color;
}			t_draw_info;

//Matrix struct contains each map point info
typedef struct s_matrix {
	t_point				points;
	t_v3df				f_points;
	int					pos_x;
	int					pos_y;
	int					height;
	unsigned int		color;
	struct s_matrix		*next;
	struct s_matrix		*prev;
}				t_matrix;

//Camera struct contains the info for the 
typedef struct s_camera {
	float	zoom;
	int		offset_x;
	int		offset_y;
	int		rotation;
	int		projection;
}				t_camera;

//Master struct to nest other structs
typedef struct s_master {
	t_matrix	**matrix;
	t_win		win;
	t_img		mlx_img;
	t_map		map;
	t_camera	camera;
}				t_master;

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
//lst_utils.c
t_matrix		*dbllst_new(int x, int y, int color, int value);
void			dbladd_back(t_matrix **lst, t_matrix *new);
int				dbllstsize(t_matrix *lst);
void			dbllstclear(t_matrix **lst);	

//color.c
int				intermediate_color(int start, int end, float percent);
void			draw_line(t_img *data, t_matrix *current, t_matrix *next);
void			set_color(t_matrix ***head, t_map map);
int				get_col_step(int start, int end, int step, int max);

//read_map.c
int				read_map(char *map, t_img *data);

//draw_line_utils.c
int				int_part_num(float x);
void			swap_(int *a, int *b);
int				abs_(int x);

//draw.c
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);

//utils.c
unsigned int	atox(char *hex);

void			plot_grid(t_map map, t_matrix **head);
void			draw(t_img *data, t_map map, t_matrix **map_point);
void			rotate_grid(t_matrix ***result, t_map map);
void			center_grid(t_matrix ***head, t_map map);

#endif // FDF_H