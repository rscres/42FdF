/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:22:54 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/07 14:12:20 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if ((x < 0 || x > WINDOW_WIDTH) || (y < 0 || y > WINDOW_HEIGHT))
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_cam(t_camera *camera)
{
	camera->offset_x = WINDOW_WIDTH / 2;
	camera->offset_y = WINDOW_HEIGHT / 2;
	camera->zoom = 1;
	camera->rotation = 150;
	camera->projection = 1;
}

int	main(int argc, char **argv)
{
	t_master	master;

	input_validation(argv, argc);
	init_img(&master.win, &master.mlx_img, argv[1]);
	if (!read_map(&master, argv[1]))
	{
		init_cam(&master.camera);
		img_loop(&master.win, master);
	}
	clear_array(master.matrix, master.map);
	destroy_win(&master);
	return (0);
}
