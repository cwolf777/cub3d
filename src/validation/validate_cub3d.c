/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cub3d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:19:09 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 15:19:18 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_player(t_cub3d *cub3d, t_map map)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = 0;
	while (y < map.grid_height)
	{
		x = 0;
		while (x < map.grid_width)
		{
			if (ft_strchr("NWES", map.grid[y][x]))
				player_count++;
			x++;
		}
		y++;
	}
	if (player_count != 1)
		handle_error(cub3d, "No or more than one player found");
}

void	validate_cub3d(t_cub3d cub3d)
{
	validate_player(&cub3d, cub3d.map);
	validate_grid(&cub3d);
}
