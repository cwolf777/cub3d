/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:03:36 by cwolf             #+#    #+#             */
/*   Updated: 2025/06/17 15:03:38 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	cast_horizontal_ray(t_cub3d cub3d, double angle)
{
	return (cast_ray_generic(cub3d, angle, false));
}

t_ray	cast_vertical_ray(t_cub3d cub3d, double angle)
{
	return (cast_ray_generic(cub3d, angle, true));
}

t_ray_data	init_horizontal_ray(t_cub3d cub3d, double angle)
{
	t_ray_data	data;
	int			facing;

	facing = (sin(angle) < 0);
	data.y_intercept = floor(cub3d.player.pixel_pos.y / TILE_SIZE) * TILE_SIZE;
	if (facing)
		data.y_intercept -= 0.0001;
	else
		data.y_intercept += TILE_SIZE;
	data.x_intercept = cub3d.player.pixel_pos.x
		+ (data.y_intercept - cub3d.player.pixel_pos.y) / tan(angle);
	if (facing)
		data.y_step = -TILE_SIZE;
	else
		data.y_step = TILE_SIZE;
	data.x_step = data.y_step / tan(angle);
	return (data);
}

t_ray_data	init_vertical_ray(t_cub3d cub3d, double angle)
{
	t_ray_data	data;
	int			facing;

	facing = (cos(angle) < 0);
	data.x_intercept = floor(cub3d.player.pixel_pos.x / TILE_SIZE) * TILE_SIZE;
	if (facing)
		data.x_intercept -= 0.0001;
	else
		data.x_intercept += TILE_SIZE;
	data.y_intercept = cub3d.player.pixel_pos.y
		+ (data.x_intercept - cub3d.player.pixel_pos.x) * tan(angle);
	if (facing)
		data.x_step = -TILE_SIZE;
	else
		data.x_step = TILE_SIZE;
	data.y_step = data.x_step * tan(angle);
	return (data);
}