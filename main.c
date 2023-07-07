/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:15:29 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/07 19:43:49 by rseelaen         ###   ########.fr       */
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

void	draw_grid(t_map map, t_img *data)
{
	int		dist;
	t_point	start;
	t_point	end;
	int		i;
	int		j;
	int		tmpx;
	int		tmpy;


	if (WINDOW_WIDTH / map.width >= WINDOW_HEIGHT / map.height)
	{
		dist = WINDOW_HEIGHT / map.height;
		start.x = (WINDOW_WIDTH - (map.width * dist)) / 2;
		start.y = (WINDOW_HEIGHT - (map.height * dist)) / 2;
		tmpx = start.x;
		tmpy = start.y;
	}
	else
	{
		dist = WINDOW_WIDTH / map.width;
		start.x = (WINDOW_WIDTH - (map.width * dist)) / 2;
		start.y = (WINDOW_HEIGHT - (map.height * dist)) / 2;
		tmpx = start.x;
		tmpy = start.y;
	}
	end.x = start.x + dist;
	end.y = start.y;
	i = 0;
	while (i <= map.height)
	{
		j = 0;
		while (j <= map.width)
		{
			if (j != map.width)
				drawLine(data, start, end);
			if (i != map.height)
			{
				end.x = start.x;
				end.y = start.y + dist;
				drawLine(data, start, end);
			}
			start.x += dist;
			end.x = start.x + dist;
			end.y = start.y;
			j++;
		}
		start.y += dist;
		start.x = tmpx;
		end.x = start.x + dist;
		end.y = start.y;
		i++;
	}
}

int main(int argc, char **argv)
{
	t_win	win;
	t_img	mlx_img;
	// t_point	p1;
	// t_point	p2;
	// int		**coords;

	if (argc != 2)
	{
		printf("Error\n");
		exit(1);
	}
	

	// p1.x = 400;
	// p1.y = 200;
	// p2.x = 100;
	// p2.y = 200;
	win.mlx_ptr = mlx_init();
	win.win_ptr = mlx_new_window(win.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Viewer");
	mlx_img.img = mlx_new_image(win.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_img.addr = mlx_get_data_addr(mlx_img.img, &mlx_img.bits_per_pixel,
		&mlx_img.line_length, &mlx_img.endian);
	// drawLine(&mlx_img, p1, p2);
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
