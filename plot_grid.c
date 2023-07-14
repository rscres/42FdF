/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:31:39 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/14 15:40:27 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "linked_lst.h"

static int	get_dist(t_map map, t_matrix **head)
{
	int			dist;
	t_matrix	*current;

	current = head[0];
	if (WINDOW_WIDTH / map.width >= WINDOW_HEIGHT / map.height)
		dist = WINDOW_HEIGHT / map.height;
	else
		dist = WINDOW_WIDTH / map.width;
	current->points.x = (WINDOW_WIDTH - ((map.width - 1) * dist)) / 2;
	current->points.y = (WINDOW_HEIGHT - ((map.height - 1) * dist)) / 2;
	return (dist);
}

void	plot_grid(t_map map, t_matrix **head)
{
	int				dist;
	int				i;
	int				tmpx;
	int				tmpy;
	t_matrix		*current;

	current = head[0];
	dist = get_dist(map, head);
	tmpx = current->points.x;
	tmpy = current->points.y;
	i = 0;
	while (i < map.height)
	{
		current = head[i];
		current->points.x = tmpx;
		while (current != NULL)
		{
			current->points.x = tmpx + (current->pos_x * dist);
			current->points.y = tmpy;
			current = current->next;
		}
		i++;
		tmpy += dist;
	}
}
