/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:07:55 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/21 18:29:46 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if ((x < 0 || x > WINDOW_WIDTH - 1) || (y < 0 || y > WINDOW_HEIGHT - 1))
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_matrix start, t_matrix end, t_img *mlx_img)
{
	t_draw_info	info;

	info.delta.x = end.x - start.x;
	info.delta.y = end.y - start.y;
	if (info.delta.x == 0)
		vertical_line(start, end, mlx_img);
	else if (ft_abs(info.delta.x) < ft_abs(info.delta.y))
		steep_line(start, end, info, mlx_img);
	else
		low_line(start, end, info, mlx_img);
}

int	draw(t_master *master)
{
	mlx_clear_window(master->win.mlx_ptr, master->win.win_ptr);
	color_background(&master->mlx_img, DARK_GREY);
	transform(master);
	return (0);
}
