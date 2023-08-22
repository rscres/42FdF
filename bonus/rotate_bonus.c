/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:19:39 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/22 15:47:50 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	rotate_x(t_matrix *point, float angle)
{
	t_v3df	temp;

	temp.y = point->f_point.y * cos(angle) - point->f_point.z * sin(angle);
	temp.z = point->f_point.y * sin(angle) + point->f_point.z * cos(angle);
	point->f_point.y = temp.y;
	point->f_point.z = temp.z;
}

void	rotate_y(t_matrix *point, float angle)
{
	t_v3df	temp;

	temp.x = point->f_point.x * cos(angle) + point->f_point.z * sin(angle);
	temp.z = -point->f_point.x * sin(angle) + point->f_point.z * cos(angle);
	point->f_point.x = temp.x;
	point->f_point.z = temp.z;
}

void	rotate_z(t_matrix *point, float angle)
{
	t_v3df	temp;

	temp.x = point->f_point.x * cos(angle) - point->f_point.y * sin(angle);
	temp.y = point->f_point.x * sin(angle) + point->f_point.y * cos(angle);
	point->f_point.x = temp.x;
	point->f_point.y = temp.y;
}

void	rotate(t_matrix *start, t_matrix *end, t_camera cam)
{
	rotate_x(start, cam.rot.x);
	rotate_x(end, cam.rot.x);
	rotate_y(start, cam.rot.y);
	rotate_y(end, cam.rot.y);
	rotate_z(start, cam.rot.z);
	rotate_z(end, cam.rot.z);
}

void	add_angle(int key, t_master *master)
{
	float	angle;

	angle = 5 * (M_PI / 180);
	if (key == XK_KP_Up && master->camera.rot.x + angle < RAD_35)
		master->camera.rot.x += angle;
	else if (key == XK_KP_Down && master->camera.rot.x - angle > -RAD_55)
		master->camera.rot.x -= angle;
	else if (key == XK_KP_Left && master->camera.rot.y + angle < RAD_55)
		master->camera.rot.y += angle;
	else if (key == XK_KP_Right && master->camera.rot.y - angle > -RAD_35)
		master->camera.rot.y -= angle;
	else if (key == XK_KP_Home)
		master->camera.rot.z += angle;
	else if (key == XK_KP_Page_Up)
		master->camera.rot.z -= angle;
}
