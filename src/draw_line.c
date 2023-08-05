/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:16:56 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/03 11:23:40 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_loop(t_draw_info *info, t_matrix *current, t_matrix *next,
	t_img *data)
{
	int	x;

	x = info->x1;
	while (x <= info->x2)
	{
		if (info->steep)
		{
			my_mlx_pixel_put(data, int_part_num(info->intersect), x,
				info->color);
			info->color = current->color;
			// info->color = intermediate_color(next->color, current->color,
			// 		info->intersect / 255);
		}
		else
		{
			my_mlx_pixel_put(data, x, int_part_num(info->intersect),
				info->color);
			info->color = current->color;
			// info->color = intermediate_color(current->color, next->color,
			// 		info->intersect / 255);
		}
		info->color = next->color;
		info->intersect += info->slope;
		x++;
	}
}

static void	set_info(t_draw_info *info, t_matrix *current, t_matrix *next)
{
	info->color = current->color;
	info->col_step = 0;
	if (current->height != next->height && current->color != next->color)
		info->col_step = sqrt(pow(current->points.x - next->points.x, 2)
				+ pow(current->points.y - next->points.y, 2))
			/ ft_abs(next->height - current->height) / 100;
	info->steep = ft_abs(next->points.y - current->points.y)
		> ft_abs(next->points.x - current->points.x);
}

void	draw_line(t_img *data, t_matrix *current, t_matrix *next)
{
	t_draw_info	info;
	t_delta		delta;
	t_point		p1;
	t_point		p2;

	p1.x = current->points.x;
	p1.y = current->points.y;
	p2.x = next->points.x;
	p2.y = next->points.y;
	set_info(&info, current, next);
	if (info.steep)
	{
		ft_swap(&p1.x, &p1.y);
		ft_swap(&p2.x, &p2.y);
	}
	if (p1.x > p2.x)
	{
		ft_swap(&p1.x, &p2.x);
		ft_swap(&p1.y, &p2.y);
		info.color = next->color;
	}
	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	info.slope = delta.y / delta.x;
	if (delta.x == 0.0)
		info.slope = 1;
	info.x1 = p1.x;
	info.x2 = p2.x;
	info.intersect = p1.y;
	draw_loop(&info, current, next, data);
}
