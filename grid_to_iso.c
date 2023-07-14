/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_to_iso.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:00:59 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/14 20:21:25 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "linked_lst.h"

// void	to_iso(t_point *coords)
// {
// 	int		matrix[3][3];
// 	// t_point	new_coord;

// 	matrix[0][0] = coords->x * sqrt(3);
// 	matrix[1][0] = coords->x * 1;
// 	matrix[2][0] = coords->x * sqrt(2);
// 	matrix[0][1] = coords->y * 0;
// 	matrix[1][1] = coords->y * 2;
// 	matrix[2][1] = coords->y * -(sqrt(2));
// 	matrix[0][2] = coords->z * -(sqrt(3));
// 	matrix[1][2] = coords->z * 1;
// 	matrix[2][2] = coords->z * sqrt(2);
// 	coords->x = (1 / sqrt(6)) * (matrix[0][0] + matrix[0][1] + matrix[0][2]);
// 	coords->y = (1 / sqrt(6)) * (matrix[1][0] + matrix[1][1] + matrix[1][2]);
// 	coords->z = (1 / sqrt(6)) * (matrix[2][0] + matrix[2][1] + matrix[2][2]);

// 	coords->x *= 1;
// 	coords->y *= 1;
// 	coords->z *= 0;
// }

void to_iso(t_matrix *matrix)
{
	int		array[3][3];

	printf("%d\t", matrix->points.x);
	array[0][0] = matrix->points.x * sqrt(3);
	array[1][0] = matrix->points.x * 1;
	array[2][0] = matrix->points.x * sqrt(2);
	array[0][1] = matrix->points.y * 0;
	array[1][1] = matrix->points.y * 2;
	array[2][1] = matrix->points.y * -(sqrt(2));
	array[0][2] = matrix->points.z * -(sqrt(3));
	array[1][2] = matrix->points.z * 1;
	array[2][2] = matrix->points.z * sqrt(2);

	matrix->points.x = (1 / sqrt(6)) * (array[0][0] + array[0][1] + array[0][2]);
	matrix->points.y = (1 / sqrt(6)) * (array[1][0] + array[1][1] + array[1][2]);
	matrix->points.z = (1 / sqrt(6)) * (array[2][0] + array[2][1] + array[2][2]);

	matrix->points.x *= 1;
	matrix->points.y *= 1;
	matrix->points.z *= 0;

	printf("%d\n", matrix->points.x);

    // matrix->points.x = matrix->pos_x * sqrt(3);
    // matrix->points.y = matrix->pos_x + matrix->pos_y * 2;
    // matrix->points.z = matrix->pos_y * -(sqrt(2));

    // matrix->points.x *= (1 / sqrt(6));
    // matrix->points.y *= (1 / sqrt(6));
    // matrix->points.z *= (1 / sqrt(6));
}

// void to_iso(t_matrix *matrix) {
//     matrix->points.x = (sqrt(3) * matrix->pos_x) - (sqrt(3) * 0);
//     matrix->points.y = (matrix->pos_x + (2 * matrix->pos_y) + 0) / sqrt(6);
//     matrix->points.z = (-sqrt(2) * matrix->pos_x) + (-sqrt(2) * 0);
// }

void	rotate_grid(t_matrix ***result, t_map map)
{
	t_matrix *current;
	int	i;
	int	j;

	i = 0;
	printf("here\n");
	while (i < map.height)
	{
		j = 0;
		current = (*result)[i];
		while (j < map.width)
		{
			to_iso(current);
			// printf("%d\t", current->points.x);
			current = current->next;
			j++;
		}
		// printf("here\n");
		printf("\n");
		i++;
	}
	printf("\n");
}
