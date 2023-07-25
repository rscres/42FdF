/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:11:43 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/25 13:12:58 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define RED	0xff3800
# define ORANGE	0xffa000
# define BLUE	0x0057cc
# define GREEN	0x00cc44
# define YELLOW	0xffe400
# define GREY	0x91a3b0

typedef struct s_color {
	int	a;
	int	r;
	int	g;
	int	b;
}			t_color;

typedef struct s_map_colors {
	int	max_z;
	int	min_z;
	int	zero;
}			t_map_colors;

#endif //COLOR_H