/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:21:40 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/18 14:37:37 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window_size(t_cub3d *cub3d)
{
	cub3d->window_width = WINDOW_WIDTH;
	cub3d->window_height = WINDOW_HEIGHT;
}

static void	init_player(t_cub3d *cub3d)
{
	t_map		*map;
	t_player	*player;

	map = &cub3d->map;
	player = &cub3d->player;
	if (map->player_orientation == 'W')
		player->angle = convert_degree_to_rad(180);
	if (map->player_orientation == 'E')
		player->angle = convert_degree_to_rad(0);
	if (map->player_orientation == 'N')
		player->angle = convert_degree_to_rad(270);
	if (map->player_orientation == 'S')
		player->angle = convert_degree_to_rad(90);
	player->pos.x = (map->player_index.x * TILE_SIZE) + (TILE_SIZE / 2);
	player->pos.y = (map->player_index.y * TILE_SIZE) + (TILE_SIZE / 2);
	player->grid_pos.x = map->player_index.x;
	player->grid_pos.y = map->player_index.y;
	player->fov = convert_degree_to_rad(60);
}

void	init_map(t_cub3d *cub3d)
{
	cub3d->minimap_img_width = cub3d->window_width / 5;
	cub3d->minimap_img_height = cub3d->window_height / 5;
	if (cub3d->minimap_img_width < MINIMAP_WIDTH)
		cub3d->minimap_img_width = MINIMAP_WIDTH;
	if (cub3d->minimap_img_height < MINIMAP_HEIGHT)
		cub3d->minimap_img_height = MINIMAP_HEIGHT;
	cub3d->map.width = TILE_SIZE * cub3d->map.grid_width;
	cub3d->map.height = TILE_SIZE * cub3d->map.grid_height;
}

void	init_ray_caster(t_cub3d *cub3d)
{
	cub3d->ray_caster.num_rays = cub3d->window_width;
	cub3d->ray_caster.angle_step = cub3d->player.fov
		/ cub3d->ray_caster.num_rays;
	cub3d->ray_caster.dist_proj_plane = (cub3d->window_width / 2.0)
		/ tan(cub3d->player.fov / 2.0);
}

void	init_cub3d(t_cub3d *cub3d, char *path)
{
	cub3d->fd = -1;
	setup_mlx(cub3d);
	init_window_size(cub3d);
	parse_cub3d(cub3d, path);
	validate_cub3d(*cub3d);
	init_map(cub3d);
	init_player(cub3d);
	init_ray_caster(cub3d);
	create_view(cub3d);
	create_minimap(cub3d);
	set_layer_order(cub3d);
}
