/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_to_iso.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:00:59 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/01 00:55:11 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	to_iso(t_matrix *current)
{
	float	previous_x;
	float	previous_y;
	float	theta;

	theta = 150 * (M_PI / 180);
	previous_x = current->f_points.x;
	previous_y = current->f_points.y;
	current->f_points.x = -(previous_x + previous_y) * cos(theta);
	current->f_points.y = -(current->f_points.z * 0.25) + (previous_x
			- previous_y) * sin(theta);
}

void	rotate_grid(t_matrix ***head, t_map map)
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
			to_iso(current);
			current = current->next;
			j++;
		}
		i++;
	}
}
