/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:17:06 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/12 19:55:23 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LST_H
# define LINKED_LST_H

# include "fdf.h"

typedef struct t_map_point {
	t_point				points;
	int					pos_x;
	int					pos_y;
	int					height;
	unsigned int		color;
	struct t_map_point	*next;
	struct t_map_point	*prev;
}				t_map_point;

t_map_point	*dbllst_new(int x, int y, int color, int value);
void		dbladd_back(t_map_point **lst, t_map_point *new);
int			dbllstsize(t_map_point *lst);
void		dbllstclear(t_map_point **lst);

void	plot_grid(t_map map, t_map_point **head);
void	draw(t_img *data, t_map map, t_map_point **map_point);

#endif //LINKED_LST_H