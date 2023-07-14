/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:11:36 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/14 20:06:38 by rseelaen         ###   ########.fr       */
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

void	matrix_creator(t_matrix **head, char	*buffer, t_map map)
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

void	print(t_matrix ***head, t_map map)
{
	int	i = 0;
	int j = 0;
	t_matrix *current;

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

void	lst_walkback(t_matrix ***head, t_map map)
{
	int			i;
	t_matrix	*current;

	i = 0;
	while (i < map.width)
	{
		current = (*head)[i];
		int	j = 0;
		while (j < map.width)
		{
			current = current->prev;
			j++;
		}
		i++;
	}
}

// void draw_lines(t_matrix **matrix, int width, int height) {
//     for (int i = 0; i < height; i++) {
//         t_matrix *current = matrix[i];
//         t_matrix *nextRow = (i < height - 1) ? matrix[i + 1] : NULL;

//         while (current) {
//             t_matrix *next = current->next;

//             // Draw line to the next point in the same row
//             if (next) {
//                 draw_line(current->points, next->points);
//             }

//             // Draw line to the point in the next row
//             if (nextRow) {
//                 t_matrix *nextInRow = nextRow;
//                 while (nextInRow && nextInRow->pos_x < current->pos_x) {
//                     nextInRow = nextInRow->next;
//                 }
//                 if (nextInRow && nextInRow->pos_x == current->pos_x) {
//                     draw_line(current->points, nextInRow->points);
//                 }
//             }

//             current = next;
//         }
//     }
// }

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
	plot_grid(map, base_grid);
	print(&base_grid, map);
	iso_grid = malloc(sizeof(t_matrix *) * map.height);
	iso_grid = base_grid;
	print(&iso_grid, map);
	rotate_grid(&iso_grid, map);
	// print(&iso_grid, map);

	draw(data, map, iso_grid);
	close(fd);
	return (1);
}
