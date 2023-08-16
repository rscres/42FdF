/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 20:33:38 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/15 18:31:55 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	ft_atox(char *hex)
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

void	clear_array(t_matrix **matrix, t_map map)
{
	int	i;

	i = 0;
	while (i < map.height)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	bad_map_exit(char **split_line, t_map *map)
{
	int	x;

	x = 0;
	while (x < map->width && split_line[x])
		free(split_line[x++]);
	free(split_line);
	ft_putstr("Error: map is not well formatted\n");
	exit (1);
}
