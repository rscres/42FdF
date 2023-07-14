/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:49:41 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/14 19:48:33 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "linked_lst.h"

void	draw(t_img *data, t_map map, t_matrix **head)
{
	t_matrix	*current;
	t_matrix	*next_line;
	int			i;

	i = 0;
	while (i < map.height)
	{
		current = head[i];
		if (i != map.height - 1)
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
