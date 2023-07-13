/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:47:56 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/12 20:23:32 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	draw_grid(t_map map, t_img *data)
{
	int		dist;
	t_point	start;
	t_point	end;
	int		i;
	int		j;
	int		tmpx;
	int		tmpy;


	if (WINDOW_WIDTH / map.width > WINDOW_HEIGHT / map.height)
	{
		dist = WINDOW_HEIGHT / map.height - 1;
		start.x = (WINDOW_WIDTH - (map.width * dist)) / 2;
		start.y = (WINDOW_HEIGHT - (map.height * dist)) / 2;
	}
	else
	{
		dist = WINDOW_WIDTH / map.width - 1;
		start.x = (WINDOW_WIDTH - (map.width * dist)) / 2;
		start.y = (WINDOW_HEIGHT - (map.height * dist)) / 2;
	}
	tmpx = start.x;
	tmpy = start.y;
	end.x = start.x + dist;
	end.y = start.y;
	i = 0;
	while (i <= map.height)
	{
		j = 0;
		while (j <= map.width)
		{
			if (j != map.width)
				drawLine(data, start, end);
			if (i != map.height)
			{
				end.x = start.x;
				end.y = start.y + dist;
				drawLine(data, start, end);
			}
			start.x += dist;
			end.x = start.x + dist;
			end.y = start.y;
			j++;
		}
		start.y += dist;
		start.x = tmpx;
		end.x = start.x + dist;
		end.y = start.y;
		i++;
	}
}