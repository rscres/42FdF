/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:49:41 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/21 15:21:06 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_lst.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if ((x < 0 || x > WINDOW_WIDTH) || (y < 0 || y > WINDOW_HEIGHT))
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw(t_img *data, t_map map, t_matrix **head)
{
	t_matrix	*current;
	t_matrix	*next_line;
	int			i;

	i = 0;
	while (i < map.height && head[i])
	{
		current = head[i];
		if (i != map.height - 1)
			next_line = head[i + 1];
		while (current != NULL)
		{
			if (current->next != NULL)
				draw_line(data, current, current->next);
			if (i != map.height - 1)
				draw_line(data, current, next_line);
			current = current->next;
			if (!current)
				break ;
			if (next_line)
				next_line = next_line->next;
		}
		i++;
	}
}
