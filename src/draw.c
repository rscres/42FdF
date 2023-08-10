/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:07:55 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/09 20:22:29 by rseelaen         ###   ########.fr       */
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

// void	draw_line(t_matrix start, t_matrix end, t_img *mlx_img)
// {
// 	int dx, dy, p, x, y;

// 	dx = end.x - start.x;
// 	dy = start.y - start.y;
// 	x = start.x;
// 	y = start.y;
// 	p = 2 * dy - dx;
// 	while (x < end.x)
// 	{
// 		if (p >= 0)
// 		{
// 			my_mlx_pixel_put(mlx_img, x, y, start.color);
// 			y = y + 1;
// 			p = p + 2 * dy - 2 * dx;
// 		}
// 		else
// 		{
// 			my_mlx_pixel_put(mlx_img, x, y, start.color);
// 			p = p + 2 * dy;
// 		}
// 		x = x + 1;
// 	}
// }

// void draw_line(t_matrix start, t_matrix end, t_img *mlx_img)
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
// 		my_mlx_pixel_put(mlx_img, start.x, start.y, start.color);
// 		float y = start.y + info.slope;
// 		for (int x = start.x + 1; x < end.x; x++)
// 		{
// 			// my_mlx_pixel_put(mlx_img, x, (int)y, 1.0 - (y - floor(y)));
// 			// my_mlx_pixel_put(mlx_img, x, (int)y + 1, y - floor(y));
// 			my_mlx_pixel_put(mlx_img, x, (int)y, start.color);
// 			// my_mlx_pixel_put(mlx_img, x, (int)y + 1, start.color);
// 			y += info.slope;
// 		}
// 		// Last endpoint
// 		my_mlx_pixel_put(mlx_img, end.x, end.y, end.color);
// 	}
// 	else
// 	{
// 		if (start.y > end.y)
// 		{
// 			temp = start;
// 			start = end;
// 			end = temp;
// 			info.delta.x = -info.delta.x;
// 			info.delta.y = -info.delta.y;
// 		}
// 		info.slope = (float)info.delta.x / info.delta.y;
// 		// First endpoint
// 		my_mlx_pixel_put(mlx_img, start.x, start.y, start.color);
// 		float x = start.x + info.slope;
// 		for (int y = start.y + 1; y < end.y; y++)
// 		{
// 			// my_mlx_pixel_put(mlx_img, (int)x, y, 1.0 - (x - floor(x)));
// 			// my_mlx_pixel_put(mlx_img, (int)x + 1, y, x - floor(x));
// 			my_mlx_pixel_put(mlx_img, (int)x, y, start.color);
// 			// my_mlx_pixel_put(mlx_img, (int)x + 1, y, start.color);
// 			x += info.slope;
// 		}
// 		// Last endpoint
// 		my_mlx_pixel_put(mlx_img, end.x, end.y, end.color);
// 	}
// }

int	draw(t_master *master)
{
	transform(master);
	mlx_put_image_to_window(master->win.mlx_ptr, master->win.win_ptr,
		master->mlx_img.img, 0, 0);
	return (0);
}
