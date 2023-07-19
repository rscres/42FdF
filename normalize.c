/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:44:58 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/19 19:39:29 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "linked_lst.h"

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

void	normalize(t_matrix ***head, t_map map)
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
			current->f_points.x /= map.offset_x;
			current->f_points.y /= map.offset_y;
			current->f_points.z /= (map.max_z - map.min_z);
			current = current->next;
			j++;
		}
		i++;
	}
}

void	normalize_range(t_map map, t_v3df *normalize)
{
	normalize->x = ((float )map.width / (float )WINDOW_WIDTH) - 1.0;
	normalize->y = ((float )map.height / (float )WINDOW_HEIGHT) - 1.0;
	normalize->z = (map.max_z - map.min_z) / 2.0;
}

void	normalize_grid(t_matrix ***head, t_map map)
{
	t_matrix	*current;
	t_v3df		normalize;
	int			i;

	normalize_range(map, &normalize);
	i = 0;
	while (i < map.height)
	{
		current = (*head)[i];
		while (current)
		{
			current->f_points.x = (current->pos_x / normalize.x) - 1.0;
			current->f_points.y = (current->pos_y / normalize.y) - 1.0;
			current->f_points.z = (current->height / normalize.z) - 1.0;
			current = current->next;
		}
		i++;
	}
}