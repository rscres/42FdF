/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:59:15 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/13 20:24:48 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initial_zoom(t_matrix **matrix, t_camera *cam, t_map map)
{
	t_v3df	max;
	t_v3df	min;
	t_v3df	cur;
	int		y;
	int		x;
	float	theta;

	theta = 55 * (M_PI / 180.0);
	max.x = 0;
	max.y = 0;
	min.x = 0;
	min.y = 0;
	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			cur.x = (matrix[y][x].x - matrix[y][x].y) * (get_dist(map)
					* cam->zoom * cos(theta)) + cam->offset_x;
			cur.y = (matrix[y][x].x + matrix[y][x].y) * (get_dist(map)
					* cam->zoom * sin(theta)) - (matrix[y][x].z * 0.25) + cam->offset_y;
			if (cur.x > max.x)
				max.x = cur.x;
			if (cur.y > max.y)
				max.y = cur.y;
			if (cur.x < min.x)
				min.x = cur.x;
			if (cur.y < min.y)
				min.y = cur.y;
			x++;
		}
		y++;
	}
	printf("x:%f\t%f\n", max.x, min.x);
	printf("y:%f\t%f\n", max.y, min.y);
	cur.x = (WINDOW_WIDTH / 2.0f) + ((max.x - min.x) / 2.0f + min.x);
	cur.y = (WINDOW_HEIGHT / 2.0f) + ((max.y - min.y) / 4.0f + min.y);
	printf("cur:%f\t%f\n", cur.x, cur.y);
	if ((max.x - min.x) < (max.y - min.y))
	{
		printf("there\n");
		cam->zoom = ((max.x - min.x) / cur.x);
	}
	else
	{
		printf("here\n");
		cam->zoom = ((max.y - min.y) / cur.y);
	}
	if (cam->zoom == 0)
		cam->zoom = 1;
	cam->offset_x = cur.x / 2.0;
	cam->offset_y = cur.y / 3.0;
	printf("cur:%d\t%d\n", cam->offset_x, cam->offset_y);
}
