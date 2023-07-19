/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_to_iso.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:00:59 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/19 19:36:20 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "linked_lst.h"

void	to_iso(t_matrix *current)
{
	float	previous_x;
	float	previous_y;
	float	theta;

	theta = 150 * (M_PI / 180);
	previous_x = current->f_points.x;
	previous_y = current->f_points.y;
	current->f_points.x = -((previous_x + previous_y) * 0.7) * cos(theta);
	current->f_points.y = -(current->f_points.z * 0.2) + ((previous_x
				- previous_y) * 0.7) * sin(theta);
}

void	rotate_grid(t_matrix ***result, t_map map)
{
	t_matrix	*current;
	int			i;
	int			j;

	i = 0;
	while (i < map.height)
	{
		j = 0;
		current = (*result)[i];
		while (j < map.width)
		{
			to_iso(current);
			current = current->next;
			j++;
		}
		i++;
	}
}
