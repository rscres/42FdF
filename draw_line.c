/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:16:56 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/18 14:16:54 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	abs_(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	swap_(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	int_part_num(float x)
{
	return ((int)x);
}

void	draw_line(t_img *data, t_point p1, t_point p2)
{
	t_draw_info	info;
	t_delta		delta;
	int			x;

	// printf("draw_line\n");
	info.steep = abs_(p2.y - p1.y) > abs_(p2.x - p1.x);
	if (info.steep)
	{
		swap_(&p1.x, &p1.y);
		swap_(&p2.x, &p2.y);
	}
	if (p1.x > p2.x)
	{
		swap_(&p1.x, &p2.x);
		swap_(&p1.y, &p2.y);
	}
	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	info.slope = delta.y / delta.x;
	if (delta.x == 0.0)
		info.slope = 1;
	info.x1 = p1.x;
	info.x2 = p2.x;
	info.intersect = p1.y;
	if (info.steep)
	{
		x = info.x1;
		while (x <= info.x2)
		{
			my_mlx_pixel_put(data, int_part_num(info.intersect), x, 0x00FF0000);
			// my_mlx_pixel_put(data, int_part_num(intersect) - 1, x, 0x00FF0000);
			info.intersect += info.slope;
			x++;
		}
	}
	else
	{
		x = info.x1;
		while (x <= info.x2)
		{
			my_mlx_pixel_put(data, x, int_part_num(info.intersect), 0x00FF0000);
			// my_mlx_pixel_put(data, x, int_part_num(intersect) - 1, 0x00FF0000);
			info.intersect += info.slope;
			x++;
		}
	}
}
