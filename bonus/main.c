/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:22:54 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/15 18:37:28 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		initial_zoom(master.matrix, &master.camera, master.map);
		set_color(master.matrix, master.map);
		img_loop(&master.win, master);
	}
	clear_array(master.matrix, master.map);
	destroy_win(&master);
	return (0);
}
