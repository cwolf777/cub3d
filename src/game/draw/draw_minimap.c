/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:54:15 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/18 14:39:18 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_tile(t_map map, int start_x, int start_y, uint32_t color)
{
	int	pixel_x;
	int	pixel_y;
	int	x;
	int	y;

	y = 0;
	while (y < TILE_SIZE - 1)
	{
		x = 0;
		while (x < TILE_SIZE - 1)
		{
			pixel_x = x + start_x;
			pixel_y = y + start_y;
			if (is_inside_image(map.img, pixel_x, pixel_y))
				mlx_put_pixel(map.img, pixel_x, pixel_y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_cub3d cub3d)
{
	t_point_int	p;
	t_point_int	offset;

	clear_image(cub3d.map.img);
	draw_background(cub3d.map.img, BLACK_COLOR);
	offset.x = (int)cub3d.player.pos.x - (cub3d.minimap_img_width / 2);
	offset.y = (int)cub3d.player.pos.y - (cub3d.minimap_img_height / 2);
	p.y = 0;
	while (p.y < cub3d.map.grid_height)
	{
		p.x = 0;
		while (p.x < cub3d.map.grid_width)
		{
			if (cub3d.map.grid[p.y][p.x] == '1')
				fill_tile(cub3d.map, p.x * TILE_SIZE - offset.x, p.y
					* TILE_SIZE - offset.y, GREY_COLOR);
			else
				fill_tile(cub3d.map, p.x * TILE_SIZE - offset.x, p.y
					* TILE_SIZE - offset.y, WHITE_COLOR);
			p.x++;
		}
		p.y++;
	}
	draw_player(cub3d);
}

void	draw_ray(t_cub3d cub3d, t_ray ray)
{
	t_point	ray_end_pos;
	t_point	ray_start_pos;

	ray_start_pos = (t_point){cub3d.minimap_img_width / 2,
		cub3d.minimap_img_height / 2};
	ray_end_pos = convert_world_coord_to_minimap_coord(cub3d, ray.hit_pos.x,
			ray.hit_pos.y);
	draw_line(cub3d.ray_caster.img, ray_start_pos, ray_end_pos, YELLOW_COLOR);
}
