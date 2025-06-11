
#include "cub3d.h"

void draw_thick_pixel(mlx_image_t *img, int x, int y, int width, uint32_t color)
{
	int i;
	int	j;
	i = -width / 2;
	while (i <= width / 2)
	{
		j = -width / 2;
		while (j <= width / 2)
		{
			if (is_inside_image(img, x + i, y + j))
				mlx_put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

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