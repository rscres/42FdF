/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:17:06 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/21 15:20:45 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LST_H
# define LINKED_LST_H

# include "fdf.h"

typedef struct s_matrix {
	t_point				points;
	t_v3df				f_points;
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

int			intermediate_color(int start, int end, double percent);
void		draw_line(t_img *data, t_matrix *current, t_matrix *next);
void		set_color(t_matrix ***head, t_map map);
int			color_steped(int start, int end, int step, int max);

#endif //LINKED_LST_H