/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:22:26 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/19 19:11:02 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <stdio.h>

static void	init_min_max(t_v3df *max, t_v3df *min)
{
	max->x = 0;
	max->y = 0;
	min->x = 0;
	min->y = 0;
}

static void	set_min_max(t_v3df *max, t_v3df *min, t_v3df *cur)
{
	if (cur->x > max->x)
		max->x = cur->x;
	if (cur->y > max->y)
		max->y = cur->y;
	if (cur->x < min->x)
		min->x = cur->x;
	if (cur->y < min->y)
		min->y = cur->y;
}

static void	set_zoom(t_v3df max, t_v3df min, t_camera *cam)
{
	if (WINDOW_WIDTH / (max.x - min.x) > WINDOW_HEIGHT / (max.y - min.y))
		cam->zoom = (WINDOW_WIDTH / (max.x - min.x));
	else
		cam->zoom = (WINDOW_HEIGHT / (max.y - min.y));
	if (cam->zoom == 0)
		cam->zoom = 1;
}

void	initial_zoom(t_matrix **matrix, t_camera *cam, t_map map)
{
	t_v3df		max;
	t_v3df		min;
	t_matrix	cur;
	t_point		pos;

	init_min_max(&max, &min);
	pos.y = -1;
	while (++pos.y < map.height)
	{
		pos.x = -1;
		while (++pos.x < map.width)
		{
			cur = matrix[pos.y][pos.x];
			center(&cur, map);
			to_iso(&cur, *cam);
			cur.f_point.x = (cur.f_point.x * get_dist(map) * cam->zoom)
				+ cam->offset_x;
			cur.f_point.y = (cur.f_point.y * get_dist(map) * cam->zoom)
				+ cam->offset_y;
			set_min_max(&max, &min, &cur.f_point);
		}
	}
	printf("max: x:%f y:%f\n", max.x, max.y);
	printf("min: x:%f y:%f\n", min.x, min.y);
	set_zoom(max, min, cam);
	printf("%f\n", cam->zoom);
}

void	update_zoom(int key, t_camera *cam)
{
	if (key == XK_q)
		cam->zoom *= 1.1;
	else if (key == XK_e)
		cam->zoom *= 0.9;
}
