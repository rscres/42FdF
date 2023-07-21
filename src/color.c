/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:43:00 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/21 19:43:17 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "linked_lst.h"

int	color_steped(int start, int end, int step, int max)
{
	int		red;
	int		green;
	int		blue;
	int		color;

	red = (start >> 16) & 0xFF;
	green = (start >> 8) & 0xFF;
	blue = start & 0xFF;
	red += ((end >> 16) & 0xFF - red) * step / max;
	green += ((end >> 8) & 0xFF - green) * step / max;
	blue += ((end) & 0xFF - blue) * step / max;
	color = (red << 16) | (green << 8) | blue;
	return (color);
}

// void	intermediate_color(t_matrix *current, t_map map)
// {
// 	float	percent;

// 	if (abs(map.max_z) > abs(map.min_z))
// 		percent = ((current->height - map.min_z) * 1.0) / ((map.max_z - map.min_z) * 1.0);
// 	else
// 		percent = (current->height - map.max_z) * 1.0 / (map.min_z - map.max_z) * 1.0;
// 	if (percent < 0.1)
// 		current->color = current->prev->color;
// 	else if (percent > 0.9 && current->next)
// 		current->color = current->next->color;
// 	else if (current->next)
// 		current->color = percent * current->next->color;

// }

int	intermediate_color(int start, int end, double percent)
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
			if (current->height == map.min_z && map.min_z < 0)
				current->color = BLUE;
			else if (current->height == map.max_z && map.max_z > 0)
				current->color = RED;
			else if (current->height == 0)
				current->color = GREEN;
			else if (current->height > 0)
				current->color = intermediate_color(GREEN, RED, (double)
						(current->height * 100 / map.max_z) / 100);
			else if (current->height < 0)
				current->color = intermediate_color(GREEN, BLUE, (double)
						(current->height * 100 / map.min_z) / 100);
			current = current->next;
		}
	}
}
