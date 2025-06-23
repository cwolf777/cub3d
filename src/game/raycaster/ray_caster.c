/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:49:21 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/23 13:45:59 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	calculate_hit_distance(t_dda dda)
{
	if (dda.is_vertical)
		return (dda.side_dist.x - dda.delta_dist.x);
	else
		return (dda.side_dist.y - dda.delta_dist.y);
}

t_ray	cast_ray(t_cub3d cub3d, double ray_angle)
{
	t_ray	ray;
	t_point	ray_dir;
	t_dda	dda;

	ray_dir.x = cos(ray_angle);
	ray_dir.y = sin(ray_angle);
	dda = perform_dda(cub3d, ray_dir);
	ray.distance = calculate_hit_distance(dda);
	ray.hit_pos.x = cub3d.player.pos.x + ray_dir.x * ray.distance;
	ray.hit_pos.y = cub3d.player.pos.y + ray_dir.y * ray.distance;
	ray.is_vertical = dda.is_vertical;
	return (ray);
}

void	ray_caster(t_cub3d cub3d)
{
	int		i;
	t_ray	ray;
	double	start_angle;
	double	ray_angle;

	start_angle = cub3d.player.angle - (cub3d.player.fov / 2.0);
	i = 0;
	while (i < cub3d.ray_caster.num_rays)
	{
		ray_angle = start_angle + i * cub3d.ray_caster.angle_step;
		ray = cast_ray(cub3d, ray_angle);
		if (cub3d.ray_caster.is_visible)
			draw_ray(cub3d, ray);
		render_wall_slice(cub3d, i, ray, ray_angle);
		i++;
	}
}
