/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:16:56 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/09 20:26:48 by rseelaen         ###   ########.fr       */
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
			my_mlx_pixel_put(data, (int)info->intersect, x,
				info->color);
			info->color = current->color;
			// info->color = intermediate_color(next->color, current->color,
			// 		info->intersect / 255);
		}
		else
		{
			my_mlx_pixel_put(data, x, (int)info->intersect,
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
	if (current->z != next->z && current->color != next->color)
		info->col_step = sqrt(pow(current->x - next->x, 2)
				+ pow(current->y - next->y, 2))
			/ ft_abs(next->z - current->z) / 100;
	info->steep = ft_abs(next->y - current->y)
		> ft_abs(next->x - current->x);
}

void	draw_line_old(t_img *data, t_matrix *current, t_matrix *next)
{
	t_draw_info	info;
	t_point		delta;
	t_point		p1;
	t_point		p2;

	p1.x = current->x;
	p1.y = current->y;
	p2.x = next->x;
	p2.y = next->y;
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
	info.slope = 1;
	if (delta.x != 0.0)
		info.slope = delta.y / delta.x;
	info.x1 = p1.x;
	info.x2 = p2.x;
	info.intersect = p1.y;
	draw_loop(&info, current, next, data);
}
