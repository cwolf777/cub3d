
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

void	draw_filled_circle(mlx_image_t *img, t_point center, int radius, uint32_t color)
{
	int x;
	int y;
	int dx;
	int dy;
	int r_squared;
	
	r_squared = radius * radius;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			dx = center.x + x;
			dy = center.y + y;
			if (x * x + y * y <= r_squared)
				mlx_put_pixel(img, dx, dy, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_cub3d *cub3d)
{
	t_point	start;
	t_point	end;


	start.x = PLAYER_RADIUS;
	start.y = PLAYER_RADIUS;
	draw_filled_circle(cub3d->player_img, start, PLAYER_RADIUS, PLAYER_COLOR);
	end.x = start.x + cos(cub3d->player.angle) * PLAYER_RADIUS;
	end.y = start.y + sin(cub3d->player.angle) * PLAYER_RADIUS;
	draw_line(cub3d->player_img, start, end, 2, DIR_LINE_COLOR);
}
