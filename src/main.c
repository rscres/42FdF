/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:15:29 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/25 18:58:49 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_key_input(int key, t_win *win)
{
	if (key == KEY_ESCAPE)
	{
		mlx_loop_end(win->mlx_ptr);
		exit(0);
	}
	return (0);
}

int	on_close(t_win *win)
{
	mlx_loop_end(win->mlx_ptr);
	return (0);
}

int	handle_no_event(void)
{
	return (0);
}

void	init_img(t_win *win, t_img *mlx_img, char *argv)
{
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			argv);
	mlx_img->img = mlx_new_image(win->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_img->addr = mlx_get_data_addr(mlx_img->img, &mlx_img->bits_per_pixel,
			&mlx_img->line_length, &mlx_img->endian);
}

void	img_loop(t_win *win, t_img *mlx_img)
{
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, mlx_img->img, 0, 0);
	mlx_loop_hook(win->mlx_ptr, &handle_no_event, win);
	mlx_key_hook(win->win_ptr, &handle_key_input, win);
	mlx_hook(win->win_ptr, 17, 0, on_close, win);
	mlx_loop(win->mlx_ptr);
}

int main(int argc, char **argv)
{
	t_master	master;

	if (argc < 2 || !argv)
	{
		printf("Not enough arguments\n");
		exit(1);
	}
	if (argc > 2)
	{
		printf("Too many arguments\n");
		exit(1);
	}
	if (!ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])))
	{
		printf("Not a valid map file\n");
		exit(1);
	}
	init_img(&master.win, &master.mlx_img, argv[1]);
	read_map(argv[1], &master.mlx_img);
	img_loop(&master.win, &master.mlx_img);
	mlx_destroy_image(master.win.mlx_ptr, master.mlx_img.img);
	mlx_destroy_window(master.win.mlx_ptr, master.win.win_ptr);
	mlx_destroy_display(master.win.mlx_ptr);
	free(master.win.mlx_ptr);
	return (0);
}
