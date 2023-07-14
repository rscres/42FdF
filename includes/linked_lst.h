/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:17:06 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/14 19:21:17 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LST_H
# define LINKED_LST_H

# include "fdf.h"

typedef struct s_matrix {
	t_point				points;
	int					pos_x;
	int					pos_y;
	int					height;
	unsigned int		color;
	struct s_matrix		*next;
	struct s_matrix		*prev;
}				t_matrix;

t_matrix	*dbllst_new(int x, int y, int color, int value);
void		dbladd_back(t_matrix **lst, t_matrix *new);
int			dbllstsize(t_matrix *lst);
void		dbllstclear(t_matrix **lst);

void		plot_grid(t_map map, t_matrix **head);
void		draw(t_img *data, t_map map, t_matrix **map_point);
void		rotate_grid(t_matrix ***result, t_map map);

#endif //LINKED_LST_H