/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:26:56 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/19 14:39:52 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	move_y(int value, t_camera *cam)
{
	cam->offset_y += value;
}

void	move_x(int value, t_camera *cam)
{
	cam->offset_x += value;
}
