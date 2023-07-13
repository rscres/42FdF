/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:16:56 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/12 20:11:09 by rseelaen         ###   ########.fr       */
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

int int_part_num(float x)
{
    return (int)x;
}

// int	color_set(float gradient)
// {
	
// }

void	draw_line(t_img *data, t_point p1, t_point p2)
{
	int		steep;
	t_delta	delta;
	t_point	pxl;
	float	intersect;
	float	slope;
	// int		color;
	// int		color_step;

	// printf("draw_line\n");
	steep = abs_(p2.y - p1.y) > abs_(p2.x - p1.x);
	if (steep)
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
	slope = delta.y / delta.x;
	if (delta.x == 0.0)
		slope = 1;
	pxl.x = p1.x;
	pxl.y = p2.x; // not really y, actually x2
	intersect = p1.y;
	if (steep)
	{
		int x = pxl.x;
		while (x <= pxl.y)
		{
			my_mlx_pixel_put(data, int_part_num(intersect), x, 0x00FF0000);
			// my_mlx_pixel_put(data, int_part_num(intersect) - 1, x, 0x00FF0000);
			intersect += slope;
			x++;
		}
	}
	else
	{
		int x = pxl.x;
		while (x <= pxl.y)
		{
			my_mlx_pixel_put(data, x, int_part_num(intersect), 0x00FF0000);
			// my_mlx_pixel_put(data, x, int_part_num(intersect) - 1, 0x00FF0000);
			intersect += slope;
			x++;
		}
	}
}
