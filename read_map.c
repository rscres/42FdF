/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:11:36 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/19 20:26:09 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "linked_lst.h"
#include "transform.h"

static void	map_size(char *buffer, t_map *map)
{
	char	*temp;

	if (!buffer && !*buffer)
		return ;
	temp = buffer;
	map->height = 0;
	while (temp && *temp)
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
	}
	else
		dbladd_back(&head[i], dbllst_new(j, i, GREEN, ft_atoi(line[j])));
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
		{
			printf("%s ", line[j]);
			data_setter(head, j, i, line);
			j++;
		}
		printf("\n");
		free(line);
		i++;
	}
	free(split_map);
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

void	print_f(t_matrix ***head, t_map map)
{
	int			i;
	int			j;
	t_matrix	*current;

	i = 0;
	j = 0;
	while (i < map.height)
	{
		current = (*head)[i];
		j = 0;
		while (j < map.width)
		{
			printf("%.2f\t", current->f_points.x);
			j++;
			current = current->next;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}

void	print_i(t_matrix ***head, t_map map)
{
	int			i;
	int			j;
	t_matrix	*current;

	i = 0;
	j = 0;
	while (i < map.height)
	{
		current = (*head)[i];
		j = 0;
		while (j < map.width)
		{
			printf("%d\t", current->points.x);
			j++;
			current = current->next;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}

int	read_map(char *map_file, t_img *data)
{
	int			fd;
	char		buffer[65535];
	t_map		map;
	t_matrix	**base_grid;
	t_matrix	**iso_grid;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (0);
	ft_bzero(buffer, 65535);
	if (read(fd, buffer, 65535) < 0)
		return (0);
	map_size(buffer, &map);
	base_grid = malloc(sizeof(t_matrix *) * map.height);
	matrix_creator(base_grid, buffer, map);
	get_z_offset(&base_grid, &map);
	center_grid(&base_grid, map);
	iso_grid = malloc(sizeof(t_matrix *) * map.height);
	iso_grid = base_grid;
	rotate_grid(&iso_grid, map);
	plot_grid(map, iso_grid);
	draw(data, map, iso_grid);
	close(fd);
	for (int i = 0; i < map.height; i++)
	{
		dbllstclear(&iso_grid[i]);
		dbllstclear(&base_grid[i]);
	}
	dbllstclear(iso_grid);
	dbllstclear(base_grid);
	return (1);
}
