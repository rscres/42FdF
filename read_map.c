/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:11:36 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/07 19:40:54 by rseelaen         ###   ########.fr       */
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

// int	atox(char *str)
// {
// 	char	base[16];
// 	int		num;

// 	base = "0123456789ABCDEF";
// 	while (ft_strchr(base, *str))
// 		num = num * 10 + (*str++ - '0');
// }

void	data_setter(t_map_point **head, int j, int i, char **line)
{
	int		color;
	int		height;
	char	**values;

	if (ft_strchr(line[j], ','))
	{
		values = ft_split(line[j], ',');
		color = (int)strtol(values[1], NULL, 16);
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
	// int i = 0;
	// int j = 0;
	// while (j < map.height)
	// {
	// 	printf("%d\t", j);
	// 	while (i < map.width)
	// 	{
	// 		printf("%d\t", map_points[j]->color);
	// 		i++;
	// 		map_points[j] = map_points[j]->next;
	// 	}
	// 	printf("\n");
	// 	i = 0;
	// 	j++;
	// }
	draw_grid(map, data);
	close(fd);
	return (1);
}
