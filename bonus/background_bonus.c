/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:45:42 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/19 14:38:50 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	color_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			my_mlx_pixel_put(img, j++, i, color);
		i++;
	}
}

void	set_background(t_img *background, t_win *win)
{
	background->img = mlx_new_image(win->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	background->addr = mlx_get_data_addr(background->img,
			&background->bits_per_pixel,
			&background->line_length, &background->endian);
	color_background(background, DARK_GREY);
}
