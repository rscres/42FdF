/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:31:39 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/27 19:49:26 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


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

void	plot_grid(t_matrix ***head, t_map map)
{
	int				dist;
	int				i;
	t_matrix		*current;
	double			zoom;

	dist = get_dist(map, *head);
	i = 0;
	zoom = 0.7;
	while (i < map.height)
	{
		current = (*head)[i];
		while (current != NULL)
		{
			current->points.x = (current->f_points.x * (dist * zoom))
				+ WINDOW_WIDTH / 2;
			current->points.y = (current->f_points.y * (dist * zoom))
				+ WINDOW_HEIGHT / 2;
			current->points.z = 0;
			current = current->next;
		}
		i++;
	}
}

void	center_grid(t_matrix ***head, t_map map)
{
	t_matrix	*current;
	int			i;
	int			j;

	map.offset_x = (map.width - 1) / 2.0;
	map.offset_y = (map.height - 1) / 2.0;

	i = 0;
	while (i < map.height)
	{
		j = 0;
		current = (*head)[i];
		while (j < map.width)
		{
			current->f_points.x = current->pos_x - map.offset_x;
			current->f_points.y = -current->pos_y + map.offset_y;
			current->f_points.z = current->height - ((map.max_z - map.min_z)
					/ 2.0);
			current = current->next;
			j++;
		}
		i++;
	}
}

// void	plotter(t_master *master)
// {
// 	center_grid(&master->matrix, master->map);
// 	plot_grid(master->matrix, master->map);
// }
