/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_to_iso.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:00:59 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/09 11:34:13 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	to_iso(t_matrix *current, t_camera cam)
{
	float	previous_x;
	float	previous_y;
	float	theta;

	theta = cam.rotation * (M_PI / 180);
	previous_x = current->x;
	previous_y = current->y;
	current->x = -(previous_x + previous_y) * cos(theta);
	current->y = -(current->z * 0.25) + (previous_x
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
