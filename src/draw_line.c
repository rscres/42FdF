/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:16:56 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/25 20:24:04 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	draw_line(t_img *data, t_matrix *current, t_matrix *next)
{
	t_draw_info	info;
	t_delta		delta;
	int			x;
	t_point		p1;
	t_point		p2;
	float		temp_step;

	p1.x = current->points.x;
	p1.y = current->points.y;
	p2.x = next->points.x;
	p2.y = next->points.y;
	info.color = current->color;
	info.col_step = 0;
	if (current->height != next->height && current->color != next->color)
		info.col_step = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2))
			/ abs_(next->height - current->height) / 100;
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
	x = info.x1;
	temp_step = info.col_step;
	while (x <= info.x2)
	{
		if (info.steep)
		{
			my_mlx_pixel_put(data, int_part_num(info.intersect), x, info.color);
			// my_mlx_pixel_put(data, int_part_num(info.intersect) - 1, x,
			//	info.color);
			// info.color = get_col_step(current->color, next->color, temp_step, 10);
			info.color = intermediate_color(current->color, next->color, abs_(temp_step) / 10);
		}
		else
		{
			my_mlx_pixel_put(data, x, int_part_num(info.intersect), info.color);
			// my_mlx_pixel_put(data, x, int_part_num(info.intersect) - 1,
			//	info.color);
			// info.color = get_col_step(next->color, current->color, temp_step, 10);
			info.color = intermediate_color(next->color, current->color, abs_(temp_step) / 10);
		}
		info.intersect += info.slope;
		temp_step += info.col_step;
		x++;
	}
}
