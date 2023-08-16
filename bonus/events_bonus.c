/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:47:41 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/16 14:27:47 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>

int	handle_key_input(int key, t_master *master)
{
	if (key == XK_Escape)
	{
		mlx_loop_end(master->win.mlx_ptr);
		return (1);
	}
	if (key == XK_w)
		move_y(-10, &master->camera);
	if (key == XK_s)
		move_y(10, &master->camera);
	if (key == XK_a)
		move_x(-10, &master->camera);
	if (key == XK_d)
		move_x(10, &master->camera);
	if (key == XK_q || key == XK_e)
		update_zoom(key, &master->camera);
	if (key == XK_space)
		reset_view(master);
	if (key == XK_KP_Left || key == XK_KP_Up || key == XK_KP_Right
		|| key == XK_KP_Down || key == XK_KP_Home || key == XK_KP_Page_Up)
		add_angle(key, master);
	return (0);
}

int	on_close(t_win *win)
{
	mlx_loop_end(win->mlx_ptr);
	return (0);
}
