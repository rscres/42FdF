/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:05:18 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/09 21:04:57 by rseelaen         ###   ########.fr       */
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

static int	get_dist(t_map map)
{
	int			dist;

	if (WINDOW_WIDTH / map.width >= WINDOW_HEIGHT / map.height)
		dist = WINDOW_HEIGHT / map.height;
	else
		dist = WINDOW_WIDTH / map.width;
	return (dist);
}

void	iso_tf(t_matrix start, t_matrix end, t_camera cam, t_img *mlx_img,
	t_map map)
{
	float	theta;
	int		temp_x;
	int		dist;

	theta = cam.rotation * (M_PI / 180);
	dist = get_dist(map);
	center(&start, map);
	center(&end, map);
	temp_x = start.f_point.x;
	start.f_point.x = -(temp_x + start.y) * cos(theta);
	start.f_point.y = -(start.f_point.z * 0.25) + (temp_x - start.f_point.y) * sin(theta);
	temp_x = end.f_point.x;
	end.f_point.x = -(temp_x + end.f_point.y) * cos(theta);
	end.f_point.y = -(end.f_point.z * 0.25) + (temp_x - end.f_point.y) * sin(theta);
	start.x = (start.f_point.x * dist) + cam.offset_x;
	start.y = (start.f_point.y * dist) + cam.offset_y;
	end.x = (end.f_point.x * dist) + cam.offset_x;
	end.y = (end.f_point.y * dist) + cam.offset_y;
	printf("%d,%d\t", start.x, start.y);
	draw_line_old(mlx_img, &start, &end);
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
				// printf("%d\t", master->matrix[y][x].x);
				if (x != master->map.width - 1)
					iso_tf(master->matrix[y][x], master->matrix[y][x + 1],
						master->camera, &master->mlx_img, master->map);
				if (y != master->map.height - 1)	
					iso_tf(master->matrix[y][x], master->matrix[y + 1][x],
						master->camera, &master->mlx_img, master->map);
			}
			x++;
		}
		printf("\n");
		y++;
	}
}
