/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:54:51 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/19 15:01:09 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_cub3d cub3d)
{
	int			y;
	int			x;
	uint32_t	ceiling_color;

	ceiling_color = convert_t_rgb_to_rgb_code(cub3d.graphics.ceiling);
	y = 0;
	while (y < cub3d.window_height / 2)
	{
		x = 0;
		while (x < cub3d.window_width)
		{
			if (is_inside_image(cub3d.view_img, x, y))
				mlx_put_pixel(cub3d.view_img, x, y, ceiling_color);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_cub3d cub3d)
{
	int			y;
	int			x;
	uint32_t	floor;

	floor = convert_t_rgb_to_rgb_code(cub3d.graphics.floor);
	y = cub3d.window_height / 2;
	while (y < cub3d.window_height)
	{
		x = 0;
		while (x < cub3d.window_width)
		{
			if (is_inside_image(cub3d.view_img, x, y))
				mlx_put_pixel(cub3d.view_img, x, y, floor);
			x++;
		}
		y++;
	}
}

void	draw_wall_slice(t_cub3d cub3d, t_wall wall, int screen_column,
		int texture_offset_x)
{
	double		y_ratio;
	uint32_t	wall_color;
	int			tex_y;
	uint32_t	*pixels;
	int			y;

	y = wall.top_pixel;
	if (y < 0)
		y = 0;
	pixels = (uint32_t *)wall.texture->pixels;
	while (y < wall.bottom_pixel)
	{
		y_ratio = (double)(y - wall.top_pixel) / wall.height;
		tex_y = y_ratio * wall.texture->height;
		wall_color = pixels[tex_y * wall.texture->width + texture_offset_x];
		if (is_inside_image(cub3d.view_img, screen_column, y))
			mlx_put_pixel(cub3d.view_img, screen_column, y,
				convert_abgr_to_rgba(wall_color));
		y++;
	}
}
