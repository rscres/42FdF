/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_to_iso.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:00:59 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/25 13:18:22 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	to_iso(t_matrix *current)
{
	float	previous_x;
	float	previous_y;
	float	theta;
	float	zoom;

	theta = 150 * (M_PI / 180);
	zoom = 1;
	previous_x = current->f_points.x;
	previous_y = current->f_points.y;
	current->f_points.x = -((previous_x + previous_y) * zoom) * cos(theta);
	current->f_points.y = -(current->f_points.z * 0.25) + ((previous_x
				- previous_y) * zoom) * sin(theta);
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
