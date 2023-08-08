/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:07:55 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/08 14:58:18 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if ((x < 0 || x > WINDOW_WIDTH) || (y < 0 || y > WINDOW_HEIGHT))
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// void	drawline(int x0, int y0, int x1, int y1, t_master master)
// {
//     int dx, dy, p, x, y;

// 	dx = x1 - x0;
// 	dy = y1 - y0;
// 	x = x0;
// 	y = y0;
// 	p = 2 * dy - dx;
// 	while (x < x1)
// 	{
// 		if (p >= 0)
// 		{
// 			my_mlx_pixel_put(&master.mlx_img, x, y, 7);
// 			y = y + 1;
// 			p = p + 2 * dy - 2 * dx;
// 		}
// 		else
// 		{
// 			my_mlx_pixel_put(&master.mlx_img, x, y, 7);
// 			p = p + 2 * dy;
// 		}
// 		x = x + 1;
// 	}
// }

// void draw_line(t_matrix start, t_matrix end)
// {
// 	t_draw_info	info;
// 	t_matrix	temp;

// 	info.delta.x = end.x - start.x;
// 	info.delta.y = end.y - start.y;
// 	if (ft_abs(info.delta.x) > ft_abs(info.delta.y))
// 	{
// 		if (start.x > end.x)
// 		{
// 			temp = start;
// 			start = end;
// 			end = temp;
// 			info.delta.x = -info.delta.x;
// 			info.delta.y = -info.delta.y;
// 		}
// 		info.slope = (float)info.delta.y / info.delta.x;
// 		// First endpoint
// 		my_mlx_pixel_put(start.x, start.y, 1.0);
// 		float y = start.y + info.slope;
// 		for (int x = start.x + 1; x < end.x; x++)
// 		{
// 			my_mlx_pixel_put(x, (int)y, 1.0 - (y - floor(y)));
// 			my_mlx_pixel_put(x, (int)y + 1, y - floor(y));
// 			y += info.slope;
// 		}
// 		// Last endpoint
// 		my_mlx_pixel_put(end.x, end.y, 1.0);
// 	}
// 	else
// 	{
// 		if (start.y > end.y)
// 		{
// 			t_point temp = start;
// 			start = end;
// 			end = temp;
// 			info.delta.x = -info.delta.x;
// 			info.delta.y = -info.delta.y;
// 		}
// 		float info.slope = (float)info.delta.x / info.delta.y;
// 		// First endpoint
// 		my_mlx_pixel_put(start.x, start.y, 1.0);
// 		float x = start.x + info.slope;
// 		for (int y = start.y + 1; y < end.y; y++)
// 		{
// 			my_mlx_pixel_put((int)x, y, 1.0 - (x - floor(x)));
// 			my_mlx_pixel_put((int)x + 1, y, x - floor(x));
// 			x += info.slope;
// 		}
// 		// Last endpoint
// 		my_mlx_pixel_put(end.x, end.y, 1.0);
// 	}
// }

int	draw(t_master *master)
{
	
	my_mlx_pixel_put(&master->mlx_img, 199, 199, RED);
	mlx_put_image_to_window(master->win.mlx_ptr, master->win.win_ptr,
		master->mlx_img.img, 0, 0);
	return (0);
}
