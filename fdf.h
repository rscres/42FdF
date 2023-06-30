/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:46:30 by renato            #+#    #+#             */
/*   Updated: 2023/06/30 18:45:25 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>

# define WINDOW_WIDTH 720
# define WINDOW_HEIGHT 720

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_point {
	int		x;
	int		y;
}				t_point;

typedef struct s_triangle {
	t_point		a;
	t_point		b;
	t_point		c;
}				t_triangle;

typedef struct s_quad {
	t_point		a;
	t_point		b;
	t_point		c;
	t_point		d;
}				t_quad;

typedef struct delta {
	float	x;
	float	y;
}				t_delta;



void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif // FDF_H