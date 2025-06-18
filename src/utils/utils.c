/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:16:41 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/18 16:52:54 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**copy_grid(t_cub3d *cub3d, t_map map)
{
	char	**new_grid;
	int		i;

	i = 0;
	new_grid = malloc(sizeof(char *) * (map.grid_height + 1));
	if (!new_grid)
		handle_error(cub3d, "Malloc failed in func: copy_map");
	while (map.grid[i] != NULL)
	{
		new_grid[i] = ft_strdup(map.grid[i]);
		if (!new_grid[i])
			handle_error(cub3d, "Malloc failed in func: copy_map");
		i++;
	}
	new_grid[i] = NULL;
	return (new_grid);
}

double	get_elapsed_time(void)
{
	static double	last_frame_time = 0.0;
	double			current_time;
	double			delta_time;

	current_time = mlx_get_time();
	if (last_frame_time == 0.0)
		last_frame_time = current_time;
	delta_time = current_time - last_frame_time;
	last_frame_time = current_time;
	if (delta_time > 0.05)
		delta_time = 0.05;
	return (delta_time);
}

void	update_player_pos(t_cub3d *cub3d, double new_x, double new_y)
{
	if (!check_collision(cub3d->map, new_x, new_y))
	{
		cub3d->player.pos.x = new_x;
		cub3d->player.pos.y = new_y;
	}
	else if (!check_collision(cub3d->map, new_x, cub3d->player.pos.y))
		cub3d->player.pos.x = new_x;
	else if (!check_collision(cub3d->map, cub3d->player.pos.x, new_y))
		cub3d->player.pos.y = new_y;
	cub3d->player.grid_pos.x = (int)(cub3d->player.pos.x / TILE_SIZE);
	cub3d->player.grid_pos.y = (int)(cub3d->player.pos.y / TILE_SIZE);
}
