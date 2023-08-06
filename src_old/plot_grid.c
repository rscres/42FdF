/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:31:39 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/05 18:25:54 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_dist(t_map map)
{
	int			dist;

	if (WINDOW_WIDTH / map.width >= WINDOW_HEIGHT / map.height)
		dist = WINDOW_HEIGHT / map.height;
	else
		dist = WINDOW_WIDTH / map.width;
	return (dist);
}

void	set_zoom(void)
{
	static int	initial;

	if (initial == 0)
	{
		initial = 1;
	}
}

void	plot_grid(t_matrix ***head, t_map map)
{
    int				dist;
    int				i;
    t_matrix		*current;
    double			zoom;
    float			iso_angle = 50.0f; // replace with your isometric angle in degrees
    // int				tile_width = TILE_WIDTH; // replace with your tile width
    // int				tile_height = TILE_HEIGHT; // replace with your tile height
    float			iso_radians = iso_angle * M_PI / 180.0f;
    float			max_x = 0;
    float			max_y = 0;
    float			min_x = 0;
    float			min_y = 0;

    dist = get_dist(map);
    set_zoom();
    i = 0;
    zoom = 1;
    while (i < map.height)
    {
        current = (*head)[i];
        while (current != NULL)
        {
            float x = (current->f_points.x * (dist * zoom * cos(iso_radians)));
            float y = (current->f_points.y * (dist * zoom * sin(iso_radians)));
            current->points.x = x;
            current->points.y = y;
            current->points.z = 0;
            if (x > max_x)
                max_x = x;
            if (y > max_y)
                max_y = y;
            if (x < min_x)
                min_x = x;
            if (y < min_y)
                min_y = y;
            current = current->next;
        }
        i++;
    }
    float center_x = (max_x - min_x) / 2.0f + min_x;
    float center_y = (max_y - min_y) / 2.0f + min_y;
    float offset_x = (WINDOW_WIDTH / 2.0f) - center_x;
    float offset_y = (WINDOW_HEIGHT / 2.0f) - center_y;
    i = 0;
    while (i < map.height)
    {
        current = (*head)[i];
        while (current != NULL)
        {
            current->points.x += offset_x;
            current->points.y += offset_y;
            current = current->next;
        }
        i++;
    }
}

void	center_grid(t_matrix ***head, t_map map)
{
	t_matrix	*current;
	int			i;
	int			j;

	map.offset_x = (map.width - 1) / 2.0;
	map.offset_y = (map.height - 1) / 2.0;
	i = 0;
	while (i < map.height)
	{
		j = 0;
		current = (*head)[i];
		while (j < map.width)
		{
			current->f_points.x = current->pos_x - map.offset_x;
			current->f_points.y = -current->pos_y + map.offset_y;
			current->f_points.z = current->height - ((map.max_z - map.min_z)
					/ 2.0);
			current = current->next;
			j++;
		}
		i++;
	}
}
