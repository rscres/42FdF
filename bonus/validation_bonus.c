/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:21:17 by rseelaen          #+#    #+#             */
/*   Updated: 2023/08/06 13:22:17 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	input_validation(char **argv, int argc)
{
	if (argc < 2 || !argv)
	{
		ft_printf("Error: Not enough arguments\n");
		exit(1);
	}
	if (argc > 2)
	{
		ft_printf("Error: Too many arguments\n");
		exit(1);
	}
	if (!ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])))
	{
		ft_printf("Error: Not valid extension\n");
		exit(1);
	}
}
