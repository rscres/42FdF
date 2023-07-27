/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:15:29 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/27 17:46:00 by rseelaen         ###   ########.fr       */
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

void	print_matrix(t_matrix ***head, t_map map)
{
	for (int i = 0; i < map.height; i++)
	{
		for (int j = 0; j < map.width; j++)
		{
			printf("%d\t", (*head)[i]->points.x);
			if ((*head)[i]->next)
				(*head)[i] = (*head)[i]->next;
		}
		printf("\n");
	}
	for (int i = map.height - 1; i >= 0; i--)
	{
		for (int j = map.height - 1; j >= 0; j--)
		{
			if ((*head)[i]->prev)
				(*head)[i] = (*head)[i]->prev;
		}
	}
}

void	destroy_win(t_master *master)
{
	mlx_destroy_image(master->win.mlx_ptr, master->mlx_img.img);
	mlx_destroy_window(master->win.mlx_ptr, master->win.win_ptr);
	mlx_destroy_display(master->win.mlx_ptr);
	free(master->win.mlx_ptr);
}

int main(int argc, char **argv)
{
	t_master	master;

	if (argc < 2 || !argv)
	{
		ft_printf("Error: Not enough arguments\n");
		exit(1);
	}
	if (argc > 2)
	{
		ft_printf("Error: Too many arguments\n");
		exit(1);
	}
	if (!ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])))
	{
		ft_printf("Error: Not valid extension\n");
		exit(1);
	}
	init_img(&master.win, &master.mlx_img, argv[1]);
	read_map(argv[1], &master);
	get_z_offset(&master.matrix, &master.map);
	set_color(&master.matrix, master.map);
	center_grid(&master.matrix, master.map);
	rotate_grid(&master.matrix, master.map);
	plot_grid(&master.matrix, master.map);
	draw(&master.mlx_img, master.map, master.matrix);
	img_loop(&master.win, &master.mlx_img);
	for (int i = 0; i < master.map.height; i++)
		dbllstclear(&master.matrix[i]);
	if (master.matrix)
		free(master.matrix);
	destroy_win(&master);
	return (0);
}
