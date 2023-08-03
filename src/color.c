/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:43:00 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/01 01:13:44 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	set_transparency(int color, float transparency)
{
	int		alpha;
	int		result;

	alpha = (color >> 24) & 0xff;
	alpha = transparency * 255;
	result = (alpha << 24) | (color & 0xffffff);
	return (result);
}

int	get_col_step(int start, int end, int step, int max)
{
	int		red;
	int		green;
	int		blue;
	int		color;

	red = (start >> 16) & 0xFF;
	green = (start >> 8) & 0xFF;
	blue = start & 0xFF;
	red += ((end >> 16) & (0xFF - red)) * step / max;
	green += ((end >> 8) & (0xFF - green)) * step / max;
	blue += ((end) & (0xFF - blue)) * step / max;
	color = (red << 16) | (green << 8) | blue;
	return (color);
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
	if (current->height == map.min_z && map.min_z < 0)
		current->color = BLUE;
	else if (current->height == map.max_z && map.max_z > 0)
		current->color = RED;
	else if (current->height == 0)
		current->color = GREY;
	else if (current->height > 0)
		current->color = intermediate_color(GREY, RED, (double)
				(current->height * 100 / map.max_z) / 100);
	else if (current->height < 0)
		current->color = intermediate_color(GREY, BLUE, (double)
				(current->height * 100 / map.min_z) / 100);
}

void	set_color(t_matrix ***head, t_map map)
{
	t_matrix	*current;
	int			i;
	int			j;

	i = 0;
	while (i < map.height)
	{
		j = 0;
		current = (*head)[i++];
		while (j++ < map.width)
		{
			if (current && current->color != 0)
			{
				current = current->next;
				continue ;
			}
			set_color_loop(current, map);
			current = current->next;
		}
	}
}
