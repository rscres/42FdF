/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:11:36 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/25 20:37:29 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	map_size(char *buffer, t_map *map)
{
	char	*temp;

	if (!buffer && !*buffer)
		return ;
	temp = buffer;
	map->height = 0;
	while (temp && *temp)
	{
		if (*temp == '\n' )
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

static void	clear_array(char **line, int j)
{
	j = 0;
	while (*(line + j))
		free(*(line + j++));
	free(line);
}

void	matrix_creator(t_matrix **head, char *buffer, t_map map)
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
		head[i] = NULL;
		while (j < map.width)
			data_setter(head, j++, i, line);
		if (line)
			clear_array(line, j);
		i++;
	}
	if (split_map)
		clear_array(split_map, j);
}

void	matrix_creator(t_matrix **head, int fd, t_map map)
{
	char	buffer[65535];
	int		bytesread;
	int		line;
	int		j;

	ft_bzero(buffer, 60000);
	bytesread = read(fd, buffer, 65535);
	if (read(fd, buffer, 60000) < 0)
		return (0);
	i = 0;
	while (bytesread > 0)
	{
		while (buffer)
		{
			if (*buffer == '\n')
				line++;
			if (ft_isdigit(*buffer))
		}
		bytesread = read(fd, buffer, 65535);
	}
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

//Buffer size too big causes leaks and errors

int	read_map(char *map_file, t_img *data, t_master)
{
	int			fd;
	char		buffer[60000];
	t_map		map;
	t_matrix	**base_grid;
	t_matrix	**iso_grid;

	fd = open(map_file, O_RDONLY);
	if (fd < 0 || !data)
		return (0);
	base_grid = malloc(sizeof(t_matrix *) * map.height);
	if (!base_grid)
		return (0);
	matrix_creator(base_grid, buffer, map);
	get_z_offset(&base_grid, &map);
	set_color(&base_grid, map);
	center_grid(&base_grid, map);
	iso_grid = base_grid;
	rotate_grid(&iso_grid, map);
	plot_grid(map, iso_grid);
	draw(data, map, iso_grid);
	close(fd);
	for (int i = 0; i < map.height; i++)
		dbllstclear(&base_grid[i]);
	if (base_grid)
		free(base_grid);
	return (1);
}
