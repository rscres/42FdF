/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:59:15 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/19 17:10:08 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	update_scale(int key, t_camera *cam)
{
	if (key == XK_j)
		cam->scale += 0.125;
	if (key == XK_k)
		cam->scale -= 0.125;
}
