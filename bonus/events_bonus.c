/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:47:41 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/16 13:38:10 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_key_input(int key, t_master *master)
{
	if (key == ESCAPE)
	{
		mlx_loop_end(master->win.mlx_ptr);
		return (1);
	}
	if (key == KEY_W)
		move_y(-10, &master->camera);
	if (key == KEY_S)
		move_y(10, &master->camera);
	if (key == KEY_A)
		move_x(-10, &master->camera);
	if (key == KEY_D)
		move_x(10, &master->camera);
	if (key == KEY_R || key == KEY_T)
		update_zoom(key, &master->camera);
	if (key == SPACE)
		reset_view(master);
	return (0);
}

int	on_close(t_win *win)
{
	mlx_loop_end(win->mlx_ptr);
	return (0);
}
