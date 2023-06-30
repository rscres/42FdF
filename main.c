/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:15:29 by rseelaen          #+#    #+#             */
/*   Updated: 2023/06/29 23:51:07 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdlib.h>
#include <mlx.h>
#include <stdio.h>
#include "fdf.h"

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	drawLine(t_data *data, int x1, int x2, int y1, int y2) {
	int delta_x;
	int delta_y;
	// int slope;
	int steps;
	float inc_x;
	float inc_y;
	float x;
	float y;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	x = x1;
	y = y1;
	// slope = delta_y / delta_x;
	if (abs(delta_x) > abs(delta_y))
		steps = abs(delta_x);
	else
		steps = abs(delta_y);
	inc_x = (float )delta_x / (float )steps;
	inc_y = (float )delta_y / (float )steps;
	while (x <= x2 && y <= y2)
	{
		my_mlx_pixel_put(data, x, y, 0x00FF0000);
		x = x + inc_x;
		y = y + inc_y;
	}
}

void	draw_triangle()
{
	
}

int main(void)
{
	void	*mlx_ptr;
	t_data	mlx_img;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Viewer");
	mlx_img.img = mlx_new_image(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_img.addr = mlx_get_data_addr(mlx_img.img, &mlx_img.bits_per_pixel, &mlx_img.line_length, &mlx_img.endian);
	drawLine(&mlx_img, 200, 530, 300, 451);
	drawLine(&mlx_img, 370, 530, 300, 451);
	drawLine(&mlx_img, 200, 370, 300, 300);
	mlx_put_image_to_window(mlx_ptr, win_ptr, mlx_img.img, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}
