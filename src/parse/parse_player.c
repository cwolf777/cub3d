/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:38:05 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 14:39:11 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_player_index(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->grid_height)
	{
		x = 0;
		while (x < map->grid_width)
		{
			if (ft_strchr("NWES", map->grid[y][x]))
			{
				map->player_index.x = x;
				map->player_index.y = y;
				map->player_orientation = map->grid[y][x];
			}
			x++;
		}
		y++;
	}
}
