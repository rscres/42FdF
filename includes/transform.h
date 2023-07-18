/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:46:53 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/18 20:05:39 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H

# include "linked_lst.h"

void	plot_grid(t_map map, t_matrix **head);
void	draw(t_img *data, t_map map, t_matrix **map_point);
void	rotate_grid(t_matrix ***result, t_map map);

//normalize.c
void	center_grid(t_matrix ***head, t_map map);
void	normalize(t_matrix ***head, t_map map);

#endif // TRANSFORM_H