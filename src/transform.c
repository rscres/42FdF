/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:05:18 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/13 19:10:45 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	center(t_matrix *matrix, t_map map)
{
	float	offset_x;
	float	offset_y;

	offset_x = (map.width - 1) / 2.0;
	offset_y = (map.height - 1) / 2.0;
	matrix->f_point.x = matrix->x - offset_x;
	matrix->f_point.y = matrix->y - offset_y;
	matrix->f_point.z = matrix->z - ((map.max_z - map.min_z) / 2.0);
}

int	get_dist(t_map map)
{
	int			dist;

	if (WINDOW_WIDTH / map.width >= WINDOW_HEIGHT / map.height)
		dist = WINDOW_HEIGHT / map.height;
	else
		dist = WINDOW_WIDTH / map.width;
	return (dist);
}

void	to_iso(t_matrix *point)
{
	float	theta;

	theta = 55 * (M_PI / 180.0);
	point->f_point.x = (point->f_point.x - point->f_point.y) * cos(theta);
	point->f_point.y = (point->f_point.x + point->f_point.y) * sin(theta)
		- (point->f_point.z * 0.25);
}

void	iso_tf(t_matrix start, t_matrix end, t_camera cam, t_master *master)
{
	int			dist;
	t_matrix	start_tmp;
	t_matrix	end_tmp;

	start_tmp = start;
	end_tmp = end;
	dist = get_dist(master->map);
	center(&start_tmp, master->map);
	center(&end_tmp, master->map);
	to_iso(&start_tmp);
	to_iso(&end_tmp);
	start_tmp.x = (start_tmp.f_point.x * dist * cam.zoom) + cam.offset_x;
	start_tmp.y = (start_tmp.f_point.y * dist * cam.zoom) + cam.offset_y;
	end_tmp.x = (end_tmp.f_point.x * dist * cam.zoom) + cam.offset_x;
	end_tmp.y = (end_tmp.f_point.y * dist * cam.zoom) + cam.offset_y;
	draw_line(start_tmp, end_tmp, &master->mlx_img);
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
				if (x != master->map.width - 1)
					iso_tf(master->matrix[y][x], master->matrix[y][x + 1],
						master->camera, master);
				if (y != master->map.height - 1)
					iso_tf(master->matrix[y][x], master->matrix[y + 1][x],
						master->camera, master);
			}
			x++;
		}
		y++;
	}
}
