/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:22:54 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/21 12:06:33 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	init_cam(t_camera *camera)
{
	camera->offset_x = (WINDOW_WIDTH / 2);
	camera->offset_y = (WINDOW_HEIGHT / 2) - 50;
	camera->zoom = 1;
	camera->scale = 0.25;
	camera->projection = 1;
	camera->rot.x = 0;
	camera->rot.y = 0;
	camera->rot.z = 0;
}

int	main(int argc, char **argv)
{
	t_master	master;

	input_validation(argv, argc);
	init_img(&master.win, &master.mlx_img, argv[1]);
	if (!read_map(&master, argv[1]))
	{
		set_background(&master.background, &master.win);
		init_cam(&master.camera);
		initial_zoom(master.matrix, &master.camera, master.map);
		set_color(master.matrix, master.map);
		transform(&master);
		img_loop(&master.win, master);
	}
	clear_array(master.matrix, master.map);
	destroy_win(&master);
	return (0);
}
