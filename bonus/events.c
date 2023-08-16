/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:47:41 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/08 12:15:36 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_key_input(int key, t_win *win)
{
	if (key == KEY_ESCAPE)
	{
		mlx_loop_end(win->mlx_ptr);
		return (1);
	}
	return (0);
}

int	on_close(t_win *win)
{
	mlx_loop_end(win->mlx_ptr);
	return (0);
}
