/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:39:43 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/22 13:30:13 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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

void	set_point(t_matrix *matrix, t_point pos, char *split_line, t_map *map)
{
	matrix->x = pos.x;
	matrix->y = pos.y;
	matrix->z = ft_atoi(split_line);
	if (ft_strchr(split_line, ','))
		matrix->color = ft_atox((ft_strchr(split_line, ',') + 1));
	else
		matrix->color = 0;
	get_z(matrix->z, map);
}

void	set_coords(t_matrix **matrix, t_map *map, int fd)
{
	t_point	pos;
	char	*line;
	char	**split_line;

	pos.y = -1;
	map->max_z = 0;
	map->min_z = 0;
	while (++pos.y <= map->height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		split_line = ft_split(line, ' ');
		free(line);
		pos.x = -1;
		while (split_line[++pos.x] && pos.x < map->width)
			set_point(&matrix[pos.y][pos.x], pos,
				*(split_line + pos.x), map);
		if (pos.x != map->width)
			bad_map_exit(split_line, map);
		while (pos.x >= 0)
			free(split_line[pos.x--]);
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
	ft_printf("Loading map...\n");
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
	set_coords(master->matrix, &master->map, fd);
	close(fd);
	ft_printf("Map loaded\n");
	return (0);
}
