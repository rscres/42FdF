/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:49:41 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/12 20:24:58 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "linked_lst.h"

void	draw(t_img *data, t_map map, t_map_point **head)
{
	t_map_point	*current;
	t_map_point	*next_line;
	int			i;

	i = 0;
	while (i < map.height)
	{
		current = head[i];
		next_line = head[i + 1];
		while (current != NULL)
		{
			if (current->next != NULL)
				draw_line(data, current->points, current->next->points);
			if (i != map.height - 1)
				draw_line(data, current->points, next_line->points);
			current = current->next;
			next_line = next_line->next;
		}
		i++;
	}
}
