/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:55:51 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 11:06:15 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	update_line_values(int *x, int *y, int *err, t_line_helper *h)
// {
// 	int	e2;

// 	e2 = 2 * (*err);
// 	if (e2 > -h->dy)
// 	{
// 		*err -= h->dy;
// 		*x += h->sx;
// 	}
// 	if (e2 < h->dx)
// 	{
// 		*err += h->dx;
// 		*y += h->sy;
// 	}
// }

// void	draw_line(mlx_image_t *img, t_point start, t_point end, uint32_t color)
// {
// 	t_point_int		p;
// 	int				err;
// 	t_line_helper	h;

// 	p = (t_point_int){(int)start.x, (int)start.y};
// 	h.dx = abs((int)end.x - p.x);
// 	h.dy = abs((int)end.y - p.y);
// 	if (p.x < (int)end.x)
// 		h.sx = 1;
// 	else
// 		h.sx = -1;
// 	if (p.y < (int)end.y)
// 		h.sy = 1;
// 	else
// 		h.sy = -1;
// 	err = h.dx - h.dy;
// 	while (1)
// 	{
// 		if (is_inside_image(img, p.x, p.y))
// 			mlx_put_pixel(img, p.x, p.y, color);
// 		if (p.x == (int)end.x && p.y == (int)end.y)
// 			break ;
// 		update_line_values(&p.x, &p.y, &err, &h);
// 	}
// }

void draw_line(mlx_image_t *img, t_point start, t_point end, uint32_t color)
{
	int x;
	int y;
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;

	x = (int)start.x;
	y = (int)start.y;
	dx = abs((int)end.x - x);
	dy = abs((int)end.y - y);
	if (x < (int)end.x)
		sx = 1;
	else
		sx = -1;

	if (y < (int)end.y)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (true)
	{
		if (is_inside_image(img, x , y))
			mlx_put_pixel(img, x, y, color);
		if (x == (int)end.x && y == (int)end.y)
			break;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
}