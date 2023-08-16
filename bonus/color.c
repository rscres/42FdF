/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:43:00 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/11 19:44:41 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	interpolate_color(t_matrix start, t_matrix end, int x)
{
	double	step;
	int		result;
	t_color	color1;
	t_color	color2;

	step = (x - start.x) / (double)(end.x - start.x);
	color1.r = start.color >> 16 & 0xff;
	color1.g = start.color >> 8 & 0xff;
	color1.b = start.color & 0xff;
	color2.r = end.color >> 16 & 0xff;
	color2.g = end.color >> 8 & 0xff;
	color2.b = end.color & 0xff;
	result = (int)(color1.r + step * (color2.r - color1.r)) << 16
		| (int)(color1.g + step * (color2.g - color1.g)) << 8
		| (int)(color1.b + step * (color2.b - color1.b));
	return (result);
}

int	intermediate_color(int start, int end, float percent)
{
	int		result;
	t_color	color1;
	t_color	color2;

	color1.r = start >> 16 & 0xff;
	color1.g = start >> 8 & 0xff;
	color1.b = start & 0xff;
	color2.r = end >> 16 & 0xff;
	color2.g = end >> 8 & 0xff;
	color2.b = end & 0xff;
	result = (int)((color1.r * (1 - percent)) + color2.r * percent) << 16
		| (int)((color1.g * (1 - percent)) + color2.g * percent) << 8
		| (int)((color1.b * (1 - percent)) + color2.b * percent);
	return (result);
}

static void	set_color_loop(t_matrix *current, t_map map)
{
	if (current->z == map.min_z && map.min_z < 0)
		current->color = BLUE;
	else if (current->z == map.max_z && map.max_z > 0)
		current->color = RED;
	else if (current->z == 0)
		current->color = GREY;
	else if (current->z > 0)
	{
		if (map.max_z == 0)
			map.max_z = 1;
		current->color = intermediate_color(GREY, RED, (double)
				(current->z * 100 / map.max_z) / 100);
	}
	else if (current->z < 0)
	{
		if (map.min_z == 0)
			map.min_z = 1;
		current->color = intermediate_color(GREY, BLUE, (double)
				(current->z * 100 / map.min_z) / 100);
	}
}

void	set_color(t_matrix **matrix, t_map map)
{
	int			y;
	int			x;

	y = 0;
	while (y < map.height)
	{
		x = -1;
		while (++x < map.width)
		{
			if (matrix[y][x].color != 0)
				continue ;
			set_color_loop(&matrix[y][x], map);
		}
		y++;
	}
}
