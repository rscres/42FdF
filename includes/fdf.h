/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:46:30 by renato            #+#    #+#             */
/*   Updated: 2023/07/12 21:03:15 by rseelaen         ###   ########.fr       */
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
// # include "get_next_line/get_next_line.h"
// # include "linked_lst.h"

# define WINDOW_WIDTH 720
# define WINDOW_HEIGHT 720

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
	int	height;
	int	width;
}				t_map;

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
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

//plot_grid.c


//read_map.c
int		read_map(char *map, t_img *data);

//draw_line.c
void	draw_line(t_img *data, t_point p1, t_point p2);



#endif // FDF_H