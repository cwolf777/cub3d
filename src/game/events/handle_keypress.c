/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:25:49 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/16 16:26:11 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	toggle_rays(t_cub3d *cub3d)
{
	if (cub3d->map.is_visible)
		cub3d->ray_caster.is_visible = !cub3d->ray_caster.is_visible;
	if (!cub3d->ray_caster.is_visible)
		clear_image(cub3d->ray_caster.img);
}

static void	toggle_minimap(t_cub3d *cub3d)
{
	cub3d->map.is_visible = !cub3d->map.is_visible;
	cub3d->ray_caster.is_visible = false;
	if (!cub3d->map.is_visible)
		clear_image(cub3d->map.img);
}

void	handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (void *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		handle_close(param);
	if (keydata.key == MLX_KEY_TAB)
		toggle_minimap(cub3d);
	if (keydata.key == MLX_KEY_R)
		toggle_rays(cub3d);
}
