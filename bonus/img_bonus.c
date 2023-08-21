/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:20:23 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/21 15:14:23 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	init_img(t_win *win, t_img *mlx_img, char *argv)
{
	win->mlx_ptr = mlx_init();
	if (!win->mlx_ptr)
		return ;
	win->win_ptr = mlx_new_window(win->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			argv);
	if (!win->win_ptr)
		return ;
	mlx_img->img = mlx_new_image(win->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_img->addr = mlx_get_data_addr(mlx_img->img, &mlx_img->bits_per_pixel,
			&mlx_img->line_length, &mlx_img->endian);
}

void	img_loop(t_win *win, t_master master)
{
	mlx_loop_hook(win->mlx_ptr, &draw, &master);
	mlx_key_hook(win->win_ptr, &handle_key_input, &master);
	mlx_hook(win->win_ptr, 17, 0, on_close, win);
	mlx_loop(win->mlx_ptr);
}

void	destroy_win(t_master *master)
{
	mlx_destroy_image(master->win.mlx_ptr, master->mlx_img.img);
	mlx_destroy_window(master->win.mlx_ptr, master->win.win_ptr);
	mlx_destroy_display(master->win.mlx_ptr);
	free(master->win.mlx_ptr);
	exit (0);
}
