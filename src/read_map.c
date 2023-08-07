/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:39:43 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/07 19:00:07 by rseelaen         ###   ########.fr       */
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
	while (*temp != '\0' && *temp != '\n')
	{
		if (*(temp) != ' ' && (*(temp + 1) == ' ' || *(temp + 1) == '\0'
				|| *(temp + 1) == '\n' ))
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

void	get_z(int z, t_map *map)
{
	if (z > map->max_z)
		map->max_z = z;
	else if (z < map->min_z)
		map->min_z = z;
}

void	set_point(t_matrix *matrix, int x, int y, char *split_line)
{
	matrix->x = x;
	matrix->y = y;
	matrix->z = ft_atoi(split_line);
	if (ft_strchr(split_line, ','))
		matrix->color = ft_atox((ft_strchr(split_line, ',') + 1));
	else
		matrix->color = 0;
}

void	set_coords(t_matrix **matrix, t_map map, int fd)
{
	int		x;
	int		y;
	char	*line;
	char	**split_line;

	y = -1;
	map.max_z = 0;
	map.min_z = 0;
	while (++y <= map.height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		split_line = ft_split(line, ' ');
		free(line);
		x = -1;
		while (split_line[++x])
		{
			set_point(&matrix[y][x], x, y, *(split_line + x));
			get_z(matrix[y][x].z, &map);
		}
		while (x >= 0)
			free(split_line[x--]);
		free(split_line);
	}
}

int	read_map(t_master *master, char *map_file)
{
	int	fd;
	int	i;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (1);
	get_map_dimension(&master->map, fd);
	close(fd);
	master->matrix = (t_matrix **)malloc(sizeof(t_matrix *)
			* master->map.height);
	i = 0;
	while (i < master->map.height)
	{
		master->matrix[i] = (t_matrix *)malloc(sizeof(t_matrix)
				* master->map.width);
		i++;
	}
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (1);
	set_coords(master->matrix, master->map, fd);
	close(fd);
	return (0);
}
