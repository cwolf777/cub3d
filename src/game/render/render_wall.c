/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:58:34 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/19 15:00:10 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	fisheye_correction(double ray_dist, double ray_angle,
		double player_angle)
{
	return (ray_dist * cos(ray_angle - player_angle));
}

mlx_image_t	*get_wall_texture(t_cub3d cub3d, t_ray ray, double ray_angle)
{
	if (ray.is_vertical)
	{
		if (cos(ray_angle) < 0)
			return (cub3d.graphics.west.img);
		else
			return (cub3d.graphics.east.img);
	}
	else
	{
		if (sin(ray_angle) < 0)
			return (cub3d.graphics.north.img);
		else
			return (cub3d.graphics.south.img);
	}
}

int	calc_texture_offset_x(t_wall wall, t_ray ray)
{
	int	texture_offset_x;

	if (ray.is_vertical)
		texture_offset_x = (int)ray.hit_pos.y % TILE_SIZE;
	else
		texture_offset_x = (int)ray.hit_pos.x % TILE_SIZE;
	texture_offset_x = texture_offset_x * (wall.texture->width / TILE_SIZE);
	return (texture_offset_x);
}

void	render_wall_slice(t_cub3d cub3d, int screen_column, t_ray ray,
		double ray_angle)
{
	t_wall	wall;
	double	texture_offset_x;

	wall.texture = get_wall_texture(cub3d, ray, ray_angle);
	wall.distance = fisheye_correction(ray.distance, ray_angle,
			cub3d.player.angle);
	wall.height = (TILE_SIZE / wall.distance)
		* cub3d.ray_caster.dist_proj_plane;
	wall.top_pixel = (cub3d.window_height / 2) - (wall.height / 2);
	wall.bottom_pixel = (cub3d.window_height / 2) + (wall.height / 2);
	texture_offset_x = calc_texture_offset_x(wall, ray);
	draw_wall_slice(cub3d, wall, screen_column, texture_offset_x);
}
