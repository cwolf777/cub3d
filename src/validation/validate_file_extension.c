/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file_extension.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:19:26 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 15:19:28 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	validate_file_extension(char *path, char *extension)
{
	int		i;
	int		j;
	char	*filename;

	filename = ft_strrchr(path, '/');
	if (!filename)
		filename = path;
	else
		filename++;
	i = ft_strlen(filename) - 1;
	j = ft_strlen(extension) - 1;
	if (i == j)
		return (false);
	while (j >= 0)
	{
		if (filename[i] != extension[j])
			return (false);
		i--;
		j--;
	}
	return (true);
}
