/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:15:29 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/12 21:03:08 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>
#include "linked_lst.h"

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_win;


void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	handle_key_input(int keysym, t_win *win)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
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

int main(int argc, char **argv)
{
	t_win	win;
	t_img	mlx_img;

	if (argc != 2)
	{
		printf("Error\n");
		exit(1);
	}
	win.mlx_ptr = mlx_init();
	win.win_ptr = mlx_new_window(win.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Viewer");
	mlx_img.img = mlx_new_image(win.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_img.addr = mlx_get_data_addr(mlx_img.img, &mlx_img.bits_per_pixel,
			&mlx_img.line_length, &mlx_img.endian);
	read_map(argv[1], &mlx_img);
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, mlx_img.img, 0, 0);
	mlx_loop_hook(win.mlx_ptr, &handle_no_event, &win);
	mlx_key_hook(win.win_ptr, &handle_key_input, &win);
	mlx_hook(win.win_ptr, 17, 0, on_close, &win);
	mlx_loop(win.mlx_ptr);
	mlx_destroy_display(win.mlx_ptr);
	free(win.mlx_ptr);
	return (0);
}
