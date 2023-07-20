/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:43:00 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/20 17:55:52 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_lst.h"

int	color_step(int start, int end, int step, int max)
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

void	intermediate_color(t_matrix *current, t_map map)
{
	float	percent;

	if (abs(map.max_z) > abs(map.min_z))
		percent = ((current->height - map.min_z) * 1.0) / ((map.max_z - map.min_z) * 1.0);
	else
		percent = (current->height - map.max_z) * 1.0 / (map.min_z - map.max_z) * 1.0;
	if (percent < 0.1)
		current->color = current->prev->color;
	else if (percent > 0.9 && current->next)
		current->color = current->next->color;
	else if (current->next)
		current->color = percent * current->next->color;

}

void	get_color(t_matrix ***head, t_map map)
{
	t_matrix	*current;
	int			i;
	int			j;

	i = 0;
	while (i < map.height)
	{
		j = 0;
		current = (*head)[i];
		while (j < map.width)
		{
			if (current->height == map.min_z && map.min_z < 0
				&& current->color == 0)
				current->color = BLUE;
			else if (current->height == map.max_z && (current->color == 0
					|| current->color == GREY) && map.max_z > 0)
				current->color = RED;
			else if (current->height == 0 && current->color == 0)
				current->color = GREY;
			else if (current->color == 0 && current->prev)
				intermediate_color(current, map);
			current = current->next;
			j++;
		}
		i++;
	}
}
