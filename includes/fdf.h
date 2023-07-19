/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:46:30 by renato            #+#    #+#             */
/*   Updated: 2023/07/19 20:15:57 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"
# include "color.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_point {
	int		x;
	int		y;
	int		z;
}				t_point;

typedef struct s_delta {
	float	x;
	float	y;
}				t_delta;

typedef struct s_map {
	int		height;
	int		width;
	int		max_z;
	int		min_z;
	float	offset_x;
	float	offset_y;
	float	scale;
}				t_map;

typedef struct s_v3df {
	float	x;
	float	y;
	float	z;
}				t_v3df;

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_win;

typedef struct s_draw_info {
	float	intersect;
	float	steep;
	float	slope;
	int		x1;
	int		x2;
	int		color;
	int		color_step;
}			t_draw_info;

typedef struct s_color {
	int		p1;
	int		p2;
}				t_color;

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

//main.c

//plot_matrix.c


//read_map.c
int		read_map(char *map, t_img *data);

//draw_line.c
void	draw_line(t_img *data, t_point p1, t_point p2);

//draw.c
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);



#endif // FDF_H