/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:05:18 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/08 17:32:26 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	to_iso(t_matrix *current, t_matrix *next, t_camera cam)
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

void	transform(t_master *master)
{
	int	y;
	int	x;

	y = 0;
	while (y < master->map.height)
	{
		x = 0;
		while (x < master->map.width)
		{
			if (master->camera.projection == 1)
			{
				to_iso(&master->matrix[y][x], &master->matrix[y][x + 1],
					master->camera);
				to_iso(&master->matrix[y][x], &master->matrix[y + 1][x],
					master->camera);
			}
		}
	}
}
