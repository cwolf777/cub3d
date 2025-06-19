/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:38:54 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/19 12:59:43 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_point	calculate_delta_dist(t_point ray_dir)
{
	t_point	delta_dist;

	if (ray_dir.x == 0)
		delta_dist.x = 1e30;
	else
		delta_dist.x = fabs(TILE_SIZE / ray_dir.x);
	if (ray_dir.y == 0)
		delta_dist.y = 1e30;
	else
		delta_dist.y = fabs(TILE_SIZE / ray_dir.y);
	return (delta_dist);
}

static t_point_int	calculate_step(t_point ray_dir)
{
	t_point_int	step;

	if (ray_dir.x < 0)
		step.x = -1;
	else
		step.x = 1;
	if (ray_dir.y < 0)
		step.y = -1;
	else
		step.y = 1;
	return (step);
}

static t_point	calculate_side_dist(t_cub3d cub3d, t_point ray_dir,
		t_point_int step)
{
	t_point		side_dist;
	t_point		pos;
	t_point_int	map_pos;

	pos = cub3d.player.pos;
	map_pos = cub3d.player.grid_pos;
	if (step.x < 0)
		side_dist.x = (pos.x - map_pos.x * TILE_SIZE) / fabs(ray_dir.x);
	else
		side_dist.x = ((map_pos.x + 1) * TILE_SIZE - pos.x) / fabs(ray_dir.x);
	if (step.y < 0)
		side_dist.y = (pos.y - map_pos.y * TILE_SIZE) / fabs(ray_dir.y);
	else
		side_dist.y = ((map_pos.y + 1) * TILE_SIZE - pos.y) / fabs(ray_dir.y);
	return (side_dist);
}

static void	init_dda(t_dda *dda, t_cub3d cub3d, t_point ray_dir,
		t_point_int step)
{
	dda->grid_pos = cub3d.player.grid_pos;
	dda->side_dist = calculate_side_dist(cub3d, ray_dir, step);
	dda->delta_dist = calculate_delta_dist(ray_dir);
	dda->is_vertical = false;
}

t_dda	perform_dda(t_cub3d cub3d, t_point ray_dir)
{
	t_dda		dda;
	t_point_int	step;

	step = calculate_step(ray_dir);
	init_dda(&dda, cub3d, ray_dir, step);
	while (1)
	{
		if (dda.side_dist.x < dda.side_dist.y)
		{
			dda.side_dist.x += dda.delta_dist.x;
			dda.grid_pos.x += step.x;
			dda.is_vertical = true;
		}
		else
		{
			dda.side_dist.y += dda.delta_dist.y;
			dda.grid_pos.y += step.y;
			dda.is_vertical = false;
		}
		if (is_inside_grid(cub3d.map, dda.grid_pos))
			break ;
	}
	return (dda);
}
