/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:29:04 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/21 18:31:35 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	low_line(t_matrix start, t_matrix end, t_draw_info info,
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
				end, x));
		y += info.slope;
	}
	my_mlx_pixel_put(mlx_img, end.x, end.y, end.color);
}

void	steep_line(t_matrix start, t_matrix end, t_draw_info info,
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

void	vertical_line(t_matrix start, t_matrix end, t_img *mlx_img)
{
	t_matrix	temp;
	int			y;

	if (start.y > end.y)
	{
		temp = start;
		start = end;
		end = temp;
	}
	my_mlx_pixel_put(mlx_img, start.x, start.y, start.color);
	y = start.y + 1;
	while (y < end.y)
	{
		my_mlx_pixel_put(mlx_img, start.x, y, interpolate_color(start,
				end, y));
		y++;
	}
	my_mlx_pixel_put(mlx_img, start.x, y, end.color);
}
