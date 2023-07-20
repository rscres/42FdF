/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:31:39 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/19 19:35:17 by rseelaen         ###   ########.fr       */
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
	return (dist);
}

void	plot_grid(t_map map, t_matrix **head)
{
	int				dist;
	int				i;
	t_matrix		*current;

	dist = get_dist(map, head);
	i = 0;
	while (i < map.height)
	{
		current = head[i];
		while (current != NULL)
		{
			current->points.x = (current->f_points.x * dist) + WINDOW_WIDTH / 2;
			current->points.y = (current->f_points.y * dist)
				+ WINDOW_HEIGHT / 2;
			current->points.z = 0;
			current = current->next;
		}
		i++;
	}
}
