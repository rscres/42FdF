/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:28:42 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/31 20:37:38 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	*dbllst_new(int x, int y, int color, int value)
{
	t_matrix			*node;

	node = malloc(sizeof(t_matrix));
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

void	dbladd_back(t_matrix **lst, t_matrix *new)
{
	t_matrix	*current;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	new->prev = current;
	current->next = new;
}

int	dbllstsize(t_matrix *lst)
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

void	dbllstclear(t_matrix **lst)
{
	t_matrix	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free(*lst);
		*lst = next;
	}
	free(*lst);
}

void	lst_walkback(t_matrix ***head, t_map map)
{
	int			i;
	int			j;
	t_matrix	*current;

	i = 0;
	while (i < map.width)
	{
		current = (*head)[i];
		j = 0;
		while (j < map.width)
		{
			current = current->prev;
			j++;
		}
		i++;
	}
}