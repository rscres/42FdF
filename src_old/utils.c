/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:53:21 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/05 19:22:00 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	atox(char *hex)
{
	unsigned int	val;
	unsigned char	byte;

	val = 0;
	hex = (hex + 2);
	while (*hex && *hex != ' ' && *hex != '\n')
	{
		byte = *hex;
		if (byte >= '0' && byte <= '9')
			byte = byte - '0';
		else if (byte >= 'a' && byte <= 'f')
			byte = byte - 'a' + 10;
		else if (byte >= 'A' && byte <= 'F')
			byte = byte - 'A' + 10;
		val = (val << 4) | (byte & 0xF);
		hex++;
	}
	return (val);
}

void	clear_array(char **line)
{
	int	i;

	i = 0;
	while (*(line + i))
	{
		free(*(line + i));
		i++;
	}
	free(line);
}

void	init_camera(t_camera *camera)
{
	camera->zoom = 1;
	camera->offset_x = 0;
	camera->offset_y = 0;
	camera->projection = 1;
	camera->rotation = 0;
}
