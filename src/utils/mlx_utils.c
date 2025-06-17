/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:15:27 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 15:18:51 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_layer_order(t_cub3d *cub3d)
{
	mlx_set_instance_depth(cub3d->view_img->instances, 0);
	mlx_set_instance_depth(cub3d->map.img->instances, 1);
	mlx_set_instance_depth(cub3d->ray_caster.img->instances, 2);
}

bool	is_inside_image(mlx_image_t *img, int x, int y)
{
	if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
		return (true);
	return (false);
}

void	create_minimap(t_cub3d *cub3d)
{
	cub3d->map.img = mlx_new_image(cub3d->mlx, cub3d->minimap_img_width,
			cub3d->minimap_img_height);
	if (!cub3d->map.img)
		handle_error(cub3d, "Failed to load map_img");
	cub3d->ray_caster.img = mlx_new_image(cub3d->mlx, cub3d->minimap_img_width,
			cub3d->minimap_img_height);
	if (!cub3d->ray_caster.img)
		handle_error(cub3d, "Failed to create ray_caster image");
	mlx_image_to_window(cub3d->mlx, cub3d->ray_caster.img, 0, 0);
	mlx_image_to_window(cub3d->mlx, cub3d->map.img, 0, 0);
}

void	create_view(t_cub3d *cub3d)
{
	cub3d->view_img = mlx_new_image(cub3d->mlx, cub3d->window_width,
			cub3d->window_height);
	if (!cub3d->view_img)
		handle_error(cub3d, "Failed to create 3D view image");
	mlx_image_to_window(cub3d->mlx, cub3d->view_img, 0, 0);
}

void	setup_mlx(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", true);
	if (!cub3d->mlx)
		handle_error(cub3d, "MLX not initialized");
	mlx_set_window_limit(cub3d->mlx, MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT,
		MAX_WINDOW_WIDTH, MAX_WINDOW_HEIGHT);
}
