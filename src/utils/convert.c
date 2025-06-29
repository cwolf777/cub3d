/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:13:48 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/18 16:52:40 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	convert_t_rgb_to_rgb_code(t_rgb color)
{
	uint32_t	r;
	uint32_t	b;
	uint32_t	g;
	uint32_t	a;

	r = (uint32_t)(color.red & 0xFF) << 24;
	g = (uint32_t)(color.green & 0xFF) << 16;
	b = (uint32_t)(color.blue & 0xFF) << 8;
	a = 0xFF;
	return (r | g | b | a);
}

t_point	convert_world_coord_to_minimap_coord(t_cub3d cub3d, double world_x,
		double world_y)
{
	t_point	point;
	double	offset_x;
	double	offset_y;

	offset_x = cub3d.player.pos.x - (cub3d.minimap_img_width / 2);
	offset_y = cub3d.player.pos.y - (cub3d.minimap_img_height / 2);
	point.x = world_x - offset_x;
	point.y = world_y - offset_y;
	return (point);
}

uint32_t	convert_abgr_to_rgba(uint32_t abgr)
{
	uint8_t	a;
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;

	r = abgr & 0xFF;
	g = (abgr >> 8) & 0xFF;
	b = (abgr >> 16) & 0xFF;
	a = (abgr >> 24) & 0xFF;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

double	convert_degree_to_rad(int degree)
{
	return (degree * M_PI / 180);
}
