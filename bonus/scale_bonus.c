/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:59:15 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/16 14:18:58 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	if (WINDOW_WIDTH / (max.x - min.x) < WINDOW_HEIGHT / (max.y - min.y))
		cam->zoom = (WINDOW_WIDTH / (max.x - min.x)) * 1.3;
	else
		cam->zoom = (WINDOW_HEIGHT / (max.y - min.y)) * 1.3;
	if (cam->zoom == 0)
		cam->zoom = 1;
}

void	initial_zoom(t_matrix **matrix, t_camera *cam, t_map map)
{
	t_v3df	max;
	t_v3df	min;
	t_v3df	cur;
	t_point	pos;
	float	theta;

	theta = 55 * (M_PI / 180.0);
	init_min_max(&max, &min);
	pos.y = -1;
	while (++pos.y < map.height)
	{
		pos.x = -1;
		while (++pos.x < map.width)
		{
			cur.x = (matrix[pos.y][pos.x].x - matrix[pos.y][pos.x].y)
				* (get_dist(map) * cam->zoom * cos(theta));
			cur.y = (matrix[pos.y][pos.x].x + matrix[pos.y][pos.x].y)
				* (get_dist(map) * cam->zoom * sin(theta))
				- (matrix[pos.y][pos.x].z * 0.25);
			set_min_max(&max, &min, &cur);
		}
	}
	set_zoom(max, min, cam);
}

void	update_zoom(int key, t_camera *cam)
{
	if (key == XK_q)
		cam->zoom *= 1.1;
	else if (key == XK_e)
		cam->zoom *= 0.9;
}
