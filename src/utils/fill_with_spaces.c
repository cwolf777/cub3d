/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_with_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:44:25 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 14:45:24 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	get_max_line_length(char **grid)
{
	size_t	max;
	size_t	len;
	int		i;

	max = 0;
	i = 0;
	while (grid[i])
	{
		len = ft_strlen(grid[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static char	*create_space_filler(int len)
{
	char	*filler;

	filler = malloc(sizeof(char) * (len + 1));
	if (!filler)
		return (NULL);
	ft_memset(filler, ' ', len);
	filler[len] = '\0';
	return (filler);
}

bool	fill_with_spaces(char **grid)
{
	size_t	max_len;
	int		i;
	char	*filler;
	int		diff;
	char	*temp;

	max_len = get_max_line_length(grid);
	i = 0;
	while (grid[i])
	{
		if (ft_strlen(grid[i]) < max_len)
		{
			temp = grid[i];
			diff = max_len - ft_strlen(grid[i]);
			filler = create_space_filler(diff);
			grid[i] = ft_strjoin(temp, filler);
			free(temp);
			if (!grid[i])
				return (free(filler), false);
			free(filler);
		}
		i++;
	}
	return (true);
}
