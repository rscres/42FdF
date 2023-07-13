/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:11:36 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/12 21:03:31 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "linked_lst.h"

static void	map_size(char *buffer, t_map *map)
{
	char	*temp;

	temp = buffer;
	map->height = 0;
	while (*temp)
	{
		if (*temp == '\n')
			map->height++;
		temp++;
	}
	temp = buffer;
	map->width = 0;
	while (*temp != '\n')
	{
		if (*temp != ' ' && (*(temp + 1) == ' ' || *(temp + 1) == '\n'))
			map->width++;
		temp++;
	}
}

unsigned int	atox(char *hex)
{
	unsigned int	val;
	__uint8_t		byte;

	val = 0;
	while (*hex)
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

void	data_setter(t_map_point **head, int j, int i, char **line)
{
	unsigned int		color;
	int					height;
	char				**values;

	if (ft_strchr(line[j], ','))
	{
		values = ft_split(line[j], ',');
		color = atox(values[1] + 2);
		height = ft_atoi(values[0]);
		dbladd_back(&head[i], dbllst_new(j, i, color, height));
	}
	else
		dbladd_back(&head[i], dbllst_new(j, i, 0, ft_atoi(line[j])));
}

void	matrix_creator(t_map_point **head, char	*buffer, t_map map)
{
	char		**split_map;
	char		**line;
	int			i;
	int			j;

	split_map = ft_split(buffer, '\n');
	i = 0;
	while (i < map.height)
	{
		line = ft_split(split_map[i], ' ');
		j = 0;
		while (j < map.width)
		{
			data_setter(head, j, i, line);
			j++;
		}
		free(line);
		i++;
	}
	free(split_map);
}

int	read_map(char *map_file, t_img *data)
{
	int			fd;
	char		buffer[65535];
	t_map		map;
	t_map_point	**map_points;

	fd = open(map_file, O_RDONLY);
	read(fd, buffer, 65535);
	map_size(buffer, &map);
	map_points = malloc(sizeof(t_map_point *) * map.height);
	matrix_creator(map_points, buffer, map);
	plot_grid(map, map_points);
	draw(data, map, map_points);
	close(fd);
	return (1);
}
