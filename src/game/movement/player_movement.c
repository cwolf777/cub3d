/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:26:37 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/19 13:01:59 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_collision(t_map map, double px, double py)
{
	int		i;
	double	check_x;
	double	check_y;
	int		grid_x;
	int		grid_y;

	i = 0;
	while (i < 360)
	{
		check_x = px + cos(convert_degree_to_rad(i)) * PLAYER_SIZE * 1.3;
		check_y = py + sin(convert_degree_to_rad(i)) * PLAYER_SIZE * 1.3;
		grid_x = (int)(check_x / TILE_SIZE);
		grid_y = (int)(check_y / TILE_SIZE);
		if (grid_y < 0 || grid_y >= map.grid_height || grid_x < 0
			|| grid_x >= map.grid_width)
		{
			i += 30;
			continue ;
		}
		if (map.grid[grid_y][grid_x] == '1')
			return (true);
		i += 30;
	}
	return (false);
}

void	player_movement(t_cub3d *cub3d)
{
	double	delta_time;
	double	move_x;
	double	move_y;

	delta_time = get_elapsed_time();
	move_x = 0.0;
	move_y = 0.0;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
		move_forward(cub3d, &move_x, &move_y, delta_time);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		move_backward(cub3d, &move_x, &move_y, delta_time);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		move_left(cub3d, &move_x, &move_y, delta_time);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		move_right(cub3d, &move_x, &move_y, delta_time);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
		rotate_left(cub3d, delta_time);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
		rotate_right(cub3d, delta_time);
	update_player_pos(cub3d, cub3d->player.pos.x + move_x, cub3d->player.pos.y
		+ move_y);
}
