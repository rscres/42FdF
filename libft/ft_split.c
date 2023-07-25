/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:00:50 by rseelaen          #+#    #+#             */
/*   Updated: 2023/07/24 20:08:54 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			count++;
		s++;
	}
	return (count);
}

static void	ends(char const *s, char c, int *p, int *begin)
{
	int	end;
	int	start;

	start = *p;
	while (*s++ == c)
		start++;
	end = start;
	*begin = start;
	while (*s)
	{
		if (*s == c || *s == '\0')
		{	
			*p = end;
			break ;
		}
		end++;
		s++;
	}
	*p = end + 1;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		pos;
	int		count;
	int		begin;
	char	**arr;

	count = count_words(s, c);
	arr = (char **)malloc((count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	pos = 0;
	begin = 0;
	i = 0;
	while (i < count)
	{
		ends((s + pos), c, &pos, &begin);
		arr[i] = (char *)malloc((pos - begin + 1) * sizeof(char));
		if (!arr[i])
		{
			arr[i] = NULL;
			return (NULL);
		}
		ft_strlcpy(arr[i], (s + begin), (pos - begin + 1));
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
