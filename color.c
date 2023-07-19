/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:43:00 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/19 20:47:12 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_lst.h"
#include "fdf.h"

void	intermediate_color(t_matrix *current, t_map map)
{
	float	percent;

	percent = (current->height - map.min_z) / (map.max_z - map.min_z);
	if (percent < 0.2)
		current->color = BLUE;
	else if (percent < 0.4)
		current->color = GREEN;
	else if (percent < 0.6)
		current->color = YELLOW;
	else if (percent < 0.8)
		current->color = ORANGE;
	else
		current->color = RED;
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
			else if (current->height == map.max_z && current->color == 0)
				current->color = RED;
			else
				intermediate_color(current, map);
			current = current->next;
			j++;
		}
		i++;
	}
}
