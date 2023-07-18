/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:11:36 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/18 20:10:09 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "linked_lst.h"
#include "transform.h"

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
		dbladd_back(&head[i], dbllst_new(j, i, 0, ft_atoi(line[j])));
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
		while (j < map.width)
		{
			data_setter(head, j, i, line);
			if (head[i]->height > map.max_z)
				map.max_z = head[i]->height;
			if (head[i]->height < map.min_z)
				map.min_z = head[i]->height;
			j++;
		}
		free(line);
		i++;
	}
	free(split_map);
}

void	print(t_matrix ***head, t_map map)
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

void	normalize_range(t_map map, t_v3df *normalize)
{
	normalize->x = ((float )map.width / (float )WINDOW_WIDTH) - 1.0;
	normalize->y = ((float )map.height / (float )WINDOW_HEIGHT) - 1.0;
	normalize->z = (map.max_z - map.min_z) / 2.0;
	printf("x: %.4f\ty: %.4f\tz: %.4f\n", normalize->x, normalize->y, normalize->z);
}

void	normalize_grid(t_matrix ***head, t_map map)
{
	t_matrix	*current;
	t_v3df		normalize;

	normalize_range(map, &normalize);
	for (int i = 0; i < map.height; i++)
	{
		current = (*head)[i];
		while (current)
		{
			current->f_points.x = (current->pos_x / normalize.x) - 1.0;
			current->f_points.y = (current->pos_y / normalize.y) - 1.0;
			current->f_points.z = (current->height / normalize.z) - 1.0;
			// printf("%f\n", current->f_points.x);
			current = current->next;
		}
	}
}

int	read_map(char *map_file, t_img *data)
{
	int			fd;
	char		buffer[65535];
	t_map		map;
	t_matrix	**base_grid;
	t_matrix	**iso_grid;

	fd = open(map_file, O_RDONLY);
	read(fd, buffer, 65535);
	map_size(buffer, &map);
	base_grid = malloc(sizeof(t_matrix *) * map.height);
	matrix_creator(base_grid, buffer, map);
	print(&base_grid, map);
	// normalize(&base_grid, map);
	center_grid(&base_grid, map);
	iso_grid = malloc(sizeof(t_matrix *) * map.height);
	iso_grid = base_grid;
	print(&iso_grid, map);
	rotate_grid(&iso_grid, map);
	print(&iso_grid, map);
	plot_grid(map, iso_grid);
	print(&iso_grid, map);
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
