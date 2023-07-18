/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_to_iso.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:00:59 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/18 18:48:02 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "linked_lst.h"
#include <math.h>

// void	to_iso(t_matrix *matrix)
// {    // Convert degrees to radians
//     double theta = 60 * M_PI / 180;

//     // Apply rotation around the z-axis
//     double rotated_x = matrix->f_points.x * cos(theta) - matrix->f_points.y * sin(theta);
//     double rotated_y = matrix->f_points.x * sin(theta) + matrix->f_points.y * cos(theta);

//     // Project the rotated 3D coordinates onto the xy-plane
//     matrix->f_points.x = rotated_x;
//     matrix->f_points.y = rotated_y - matrix->points.z; // Substracting z to create the isometric effect
// }

// void	to_iso(t_matrix *matrix)
// {
// 	double		theta;
// 	double		rotated_x;
// 	double		rotated_y;

// 	theta = 45 * M_PI / 180;
// 	rotated_x = matrix->points.x * cos(theta) - matrix->points.y * sin(theta);
// 	rotated_y = matrix->points.x * sin(theta) + matrix->points.y * cos(theta);
// 	matrix->points.x = rotated_x;
// 	matrix->points.y = rotated_y - matrix->points.z;
// }

// void to_iso(t_matrix *matrix)
// {
// 	int		array[3][3];
// 	t_point	offset;

// 	// printf("%d\t", matrix->points.x);
// 	offset.x = WINDOW_WIDTH / 2;
// 	offset.y = WINDOW_HEIGHT / 2;
// 	array[0][0] = matrix->f_points.x * sqrt(3);
// 	array[1][0] = matrix->f_points.x * 1;
// 	array[2][0] = matrix->f_points.x * sqrt(2);

// 	array[0][1] = matrix->f_points.y * 0;
// 	array[1][1] = matrix->f_points.y * 2;
// 	array[2][1] = matrix->f_points.y * -(sqrt(2));
	
// 	array[0][2] = matrix->f_points.z * -(sqrt(3));
// 	array[1][2] = matrix->f_points.z * 1;
// 	array[2][2] = matrix->f_points.z * sqrt(2);

// 	matrix->f_points.x = (1 / sqrt(6)) * (array[0][0] + array[0][1] + array[0][2]);
// 	matrix->f_points.y = (1 / sqrt(6)) * (array[1][0] + array[1][1] + array[1][2]);
// 	matrix->f_points.z = (1 / sqrt(6)) * (array[2][0] + array[2][1] + array[2][2]);

// 	// matrix->f_points.x += offset.x;
// 	// matrix->f_points.y += offset.y;
// 	matrix->f_points.z *= 0;

// 	// printf("%d\n", matrix->points.x);
// }

void to_iso(t_matrix *matrix) {
	matrix->f_points.x = ((matrix->f_points.x - (matrix->f_points.z)) * cos(45)) * 1.0;
	matrix->f_points.y = ((matrix->f_points.x + (matrix->f_points.z)) * sin(45) - matrix->f_points.y) * 1.0;
}

void	rotate_grid(t_matrix ***result, t_map map)
{
	t_matrix	*current;
	int			i;
	int			j;

	i = 0;
	while (i < map.height)
	{
		j = 0;
		current = (*result)[i];
		while (j < map.width)
		{
			to_iso(current);
			// printf("%f\n", current->f_points.x);
			current = current->next;
			j++;
		}
		// printf("here\n");
		// printf("\n");
		i++;
	}
	// printf("\n");
}
