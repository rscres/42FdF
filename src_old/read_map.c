/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:11:36 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/05 19:51:01 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	get_map_height(t_master *master, char *map_file)
{
	char	*line;
	int		fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return ;
	master->map.height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		master->map.height++;
	}
	close(fd);
}

static int	read_map_loop(int fd, t_master *master, int i, int j)
{
	char	*line;
	char	*temp;
	int		invalid;
	int		pos;
	unsigned int		color;
	int					height;

	invalid = 0;
	master->map.width = 0;
	temp = NULL;
	while (i < master->map.height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = line;
		if (i == 0)
		{
			while (*temp != '\0')
			{
				if (*(temp) != ' ' && (*(temp + 1) == ' '
						|| *(temp + 1) == '\0'))
					master->map.width++;
				temp++;
			}
			temp = line;
		}
		master->matrix[i] = NULL;
		j = 0;
		while (*temp != '\0' && j < master->map.width)
		{
			pos = 0;
			while (*(temp + pos) != ' ')
			{
				if (*(temp + pos) == ',')
				{
					height = ft_atoi(temp);
					color = atox((temp + pos + 1));
					dbladd_back(&master->matrix[i], dbllst_new(j, i,
							color, height));
					while (*(temp + pos) != ' ' && *(temp + pos) != '\0')
						pos++;
					temp = (temp + pos);
					j++;
					break ;
				}
				else if (*(temp + pos) != ' ')
				{
					dbladd_back(&master->matrix[i], dbllst_new(j, i, 0,
							ft_atoi(temp)));
					while (*(temp + pos) != ' ' && *(temp + pos) != '\0')
						pos++;
					temp = (temp + pos);
					j++;
					break ;
				}
				pos++;
			}
			temp++;
		}
		if (line)
			free(line);
		if (j != master->map.width)
			invalid = 1;
		i++;
	}
	line = get_next_line(fd);
	if (line)
		free(line);
	if (invalid)
	{
		i = 0;
		while (i < master->map.height)
		{
			dbllstclear(&master->matrix[i]);
			i++;
		}
		mlx_destroy_image(master->win.mlx_ptr, master->mlx_img.img);
		printf("Error: Invalid map\n");
		return (1);
	}
	return (0);
}

int	read_map(char *map_file, t_master *master)
{
	int		fd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	get_map_height(master, map_file);
	master->matrix = malloc(sizeof(t_matrix *) * master->map.height);
	if (!master->matrix)
		return (1);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (1);
	if (read_map_loop(fd, master, i, j))
	{
		close(fd);
		free(master->matrix);
		return (1);
	}
	close(fd);
	return (0);
}
