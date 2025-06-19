/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:00:26 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/19 15:00:28 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_3d(t_cub3d cub3d)
{
	if (cub3d.map.is_visible)
		draw_minimap(cub3d);
	clear_image(cub3d.ray_caster.img);
	draw_ceiling(cub3d);
	draw_floor(cub3d);
	ray_caster(cub3d);
}
