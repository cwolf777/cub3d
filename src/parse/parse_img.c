/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:24:34 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 15:05:57 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_texture_identifier(char *line, char *identifier)
{
	int	len;

	len = ft_strlen(identifier);
	if (ft_strncmp(identifier, line, len) != 0)
		return (false);
	if (line[len] == '\0')
		return (false);
	if (!is_white_space(line[len]))
		return (false);
	return (true);
}

static void	parse_img(t_cub3d *cub3d, t_img *img, mlx_t *mlx, char *path)
{
	skip_whitespace(&path);
	init_img(cub3d, img, mlx, path);
}

void	load_texture(t_cub3d *cub3d, int *seen_flags, char *str)
{
	char	*temp;

	temp = str + 2;
	if (is_texture_identifier(str, "NO"))
	{
		parse_img(cub3d, &cub3d->graphics.north, cub3d->mlx, temp);
		seen_flags[NO]++;
	}
	else if (is_texture_identifier(str, "WE"))
	{
		parse_img(cub3d, &cub3d->graphics.west, cub3d->mlx, temp);
		seen_flags[WE]++;
	}
	else if (is_texture_identifier(str, "EA"))
	{
		parse_img(cub3d, &cub3d->graphics.east, cub3d->mlx, temp);
		seen_flags[EA]++;
	}
	else if (is_texture_identifier(str, "SO"))
	{
		parse_img(cub3d, &cub3d->graphics.south, cub3d->mlx, temp);
		seen_flags[SO]++;
	}
}
