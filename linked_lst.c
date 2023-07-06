/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:28:42 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/06 16:11:28 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "linked_lst.h"

t_map_point	*dbllst_new(int x, int y, int color, int value)
{
	t_map_point			*node;

	node = malloc(sizeof(t_map_point));
	if (!node)
		return (NULL);
	node->pos_x = x;
	node->pos_y = y;
	node->color = color;
	node->height = value;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	dbladd_back(t_map_point **lst, t_map_point *new)
{
	t_map_point	*current;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		new->prev = NULL;
		*lst = new;
	}
	else
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
		new->prev = current;
	}
}

int	dbllstsize(t_map_point *lst)
{
	int	size;

	if (!lst)
		return (0);
	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

void	dbllstclear(t_map_point **lst)
{
	t_map_point	*current;
	t_map_point	*next;

	current = *lst;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}
