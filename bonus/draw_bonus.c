/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:07:55 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/16 14:33:32 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if ((x < 0 || x > WINDOW_WIDTH - 1) || (y < 0 || y > WINDOW_HEIGHT - 1))
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	steep_line(t_matrix start, t_matrix end, t_draw_info info,
	t_img *mlx_img)
{
	t_matrix	temp;
	float		y;
	int			x;

	if (start.x > end.x)
	{
		temp = start;
		start = end;
		end = temp;
		info.delta.x = -info.delta.x;
		info.delta.y = -info.delta.y;
	}
	info.slope = (float)info.delta.y / info.delta.x;
	my_mlx_pixel_put(mlx_img, start.x, start.y, start.color);
	y = start.y + info.slope;
	x = start.x;
	while (++x < end.x)
	{
		my_mlx_pixel_put(mlx_img, x, (int)y, interpolate_color(start,
				end, (int)x));
		y += info.slope;
	}
	my_mlx_pixel_put(mlx_img, end.x, end.y, end.color);
}

void	low_line(t_matrix start, t_matrix end, t_draw_info info,
	t_img *mlx_img)
{
	t_matrix	temp;
	float		x;
	int			y;

	if (start.y > end.y)
	{
		temp = start;
		start = end;
		end = temp;
		info.delta.x = -info.delta.x;
		info.delta.y = -info.delta.y;
	}
	info.slope = (float)info.delta.x / info.delta.y;
	my_mlx_pixel_put(mlx_img, start.x, start.y, start.color);
	x = start.x + info.slope;
	y = start.y;
	while (++y < end.y)
	{
		my_mlx_pixel_put(mlx_img, (int)x, y, interpolate_color(start,
				end, (int)x));
		x += info.slope;
	}
	my_mlx_pixel_put(mlx_img, end.x, end.y, end.color);
}

void	draw_line(t_matrix start, t_matrix end, t_img *mlx_img)
{
	t_draw_info	info;

	info.delta.x = end.x - start.x;
	info.delta.y = end.y - start.y;
	if (ft_abs(info.delta.x) > ft_abs(info.delta.y))
		steep_line(start, end, info, mlx_img);
	else
		low_line(start, end, info, mlx_img);
}

int	draw(t_master *master)
{
	mlx_clear_window(master->win.mlx_ptr, master->win.win_ptr);
	color_background(&master->mlx_img, DARK_GREY);
	transform(master);
	return (0);
}
