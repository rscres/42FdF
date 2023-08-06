/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:39:43 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/06 20:40:17 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_map_dimension(t_map *map, int fd)
{
	char	*line;
	char	*temp;

	line = get_next_line(fd);
	if (!line)
		return ;
	temp = line;
	map->width = 0;
	map->height = 0;
	while (*temp != '\0')
	{
		if (*(temp) != ' ' && (*(temp + 1) == ' ' || *(temp + 1) == '\0'))
			map->width++;
		temp++;
	}
	while (line)
	{
		free(line);
		map->height++;
		line = get_next_line(fd);
	}
	free(line);
}

void	set_coords(t_matrix **matrix, t_map map, int fd)
{
	int		x;
	int		y;
	char	**line;

	y = 0;
	while (y < map.height)
	{
		line = ft_split(get_next_line(fd), ' ');
		x = 0;
		while (x < map.width)
		{
			matrix[y][x].x = x;
			matrix[y][x].y = y;
			matrix[y][x].z = ft_atoi(line[x]);
			if (ft_strchr(line[x], ','))
				matrix[y][x].color = ft_atox(ft_strchr(line[x], ','));
			else
				matrix[y][x].color = 0;
			x++;
		}
		free(line);
		y++;
	}
}

int	read_map(t_master *master, char *map_file)
{
	int		fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (1);
	get_map_dimension(&master->map, fd);
	close(fd);
	printf("%d\n", master->map.height);
	master->matrix = malloc(sizeof(t_matrix *) * master->map.height);
	for (int i = 0; i < master->map.width; i++)
	{
		master->matrix[i] = malloc(sizeof(t_matrix) * master->map.width);
	}
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (1);
	set_coords(master->matrix, master->map, fd);
	close(fd);
	for (int i = 0; i < master->map.width; i++)
	{
		free(master->matrix[i]);
	}
	free(master->matrix);
	return (0);
}
