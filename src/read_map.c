/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:11:36 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/28 18:40:49 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	data_setter(t_matrix **head, int j, int i, char **line)
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
		free(values);
	}
	else
		dbladd_back(&head[i], dbllst_new(j, i, 0, ft_atoi(line[j])));
}

void	get_z_offset(t_matrix ***head, t_map *map)
{
	t_matrix	*current;
	int			i;

	map->min_z = 0;
	map->max_z = 0;
	i = 0;
	while (i < map->height)
	{
		current = (*head)[i];
		while (current)
		{
			if (current->height < map->min_z)
				map->min_z = current->height;
			if (current->height > map->max_z)
				map->max_z = current->height;
			current = current->next;
		}
		i++;
	}
}

void	get_map_height(t_master *master, int fd)
{
	char	*line;

	master->map.height = 0;
	master->map.width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		master->map.height++;
	}
}

int	read_map(char *map_file, t_master *master)
{
	int		fd;
	char	*line;
	int		i;
	char	**split_line;
	int		j;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	get_map_height(master, fd);
	master->matrix = malloc(sizeof(t_matrix *) * master->map.height);
	if (!master->matrix)
		return (0);
	close(fd);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (0);
	while (i < master->map.height)
	{
		j = 0;
		line = get_next_line(fd);
		if (!line)
			break ;
		split_line = ft_split(line, ' ');
		free(line);
		master->matrix[i] = NULL;
		while (split_line[j])
		{
			data_setter(master->matrix, j, i, split_line);
			j++;
			if (i == 0)
				master->map.width++;
		}
		if (split_line)
			clear_array(split_line);
		if (j != master->map.width)
		{
			while (i >= 0)
			{
				dbllstclear(&master->matrix[i]);
				i--;
			}
			if (master->matrix)
				free(master->matrix);
			printf("Error: Invalid map\n");
			return (1);
		}
		i++;
	}
	line = get_next_line(fd);
	if (line)
		free(line);
	close(fd);
	return (0);
}
