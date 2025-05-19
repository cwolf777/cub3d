
#include "cub3d.h"

void	draw_line(mlx_image_t *img, t_point start,
	t_point end, int width, uint32_t color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	int	x;
	int	y;
	int	i;
	int	j;

	dx = abs(end.x - start.x);
	dy = -abs(end.y - start.y);
	sx = (start.x < end.x) ? 1 : -1;
	sy = (start.y < end.y) ? 1 : -1;
	err = dx + dy;
	x = start.x;
	y = start.y;
	while (1)
	{
		i = -width / 2;
		while (i <= width / 2)
		{
			j = -width / 2;
			while (j <= width / 2)
			{
				if (x + i >= 0 && x + i < (int)img->width && y + j >= 0 && y + j < (int)img->height)
					mlx_put_pixel(img, x + i, y + j, color);
				j++;
			}
			i++;
		}
		if (x == end.x && y == end.y)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y += sy;
		}
	}
}

void	draw_circle(mlx_image_t *img,t_point center, int radius, uint32_t color)
{
	int x = 0;
	int y = radius;
	int d = 3 - 2 * radius;

	while (y >= x)
	{
		// Acht Symmetriepunkte
		mlx_put_pixel(img, center.x + x, center.y + y, color);
		mlx_put_pixel(img, center.x - x, center.y + y, color);
		mlx_put_pixel(img, center.x + x, center.y - y, color);
		mlx_put_pixel(img, center.x - x, center.y - y, color);
		mlx_put_pixel(img, center.x + y, center.y + x, color);
		mlx_put_pixel(img, center.x - y, center.y + x, color);
		mlx_put_pixel(img, center.x + y, center.y - x, color);
		mlx_put_pixel(img, center.x - y, center.y - x, color);

		if (d < 0)
			d = d + 4 * x + 6;
		else
		{
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}

void	draw_circle_with_width(mlx_image_t *img, int cx, int cy, int radius, int width, uint32_t color)
{
	int r = radius;
	int inner = radius - width + 1;

	if (inner < 0)
		inner = 0;

	while (r >= inner)
	{
		int x = 0;
		int y = r;
		int d = 3 - 2 * r;

		while (y >= x)
		{
			// 8 Symmetriepunkte
			mlx_put_pixel(img, cx + x, cy + y, color);
			mlx_put_pixel(img, cx - x, cy + y, color);
			mlx_put_pixel(img, cx + x, cy - y, color);
			mlx_put_pixel(img, cx - x, cy - y, color);
			mlx_put_pixel(img, cx + y, cy + x, color);
			mlx_put_pixel(img, cx - y, cy + x, color);
			mlx_put_pixel(img, cx + y, cy - x, color);
			mlx_put_pixel(img, cx - y, cy - x, color);

			if (d < 0)
				d += 4 * x + 6;
			else
			{
				d += 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
		r--;
	}
}
