/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:44:58 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/18 20:01:11 by rseelaen         ###   ########.fr       */
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
			current->f_points.y = current->pos_y - map.offset_y;
			current->f_points.z = current->height;
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
			current->f_points.z /= map.height;
			current = current->next;
			j++;
		}
		i++;
	}
}
