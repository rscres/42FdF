/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa_line_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:58:05 by rseelaen          #+#    #+#             */
/*   Updated: 2023/06/30 18:47:10 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <mlx.h>

void	swap_(int *a, int *b)
{
	int		tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

float	abs_(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int	round_(float x)
{
	if (x < 0)
		return (x - 0.5);
	return (x + 0.5);
}

int

void	aa_line_draw(t_data *data, t_point *p1, t_point *p2)
{
	t_delta		delta;
	int			steps;
	int			slope;

	delta.x = p2->x - p1->x;
	delta.y = p2->y - p1->y;
	slope = delta.y / delta.x;
	if (abs_(delta.x) > abs_(delta.y))
		steps = abs_(delta.x);
	else
		steps = abs_(delta.y);
	
}
