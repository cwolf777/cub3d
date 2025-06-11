
#include "cub3d.h"

void	draw_filled_circle(mlx_image_t *img, t_point center, int radius, uint32_t color)
{
	int x;
	int y;
	double dx;
	double dy;
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
				mlx_put_pixel(img, (int)dx, (int)dy, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_cub3d cub3d)
{
	t_point	start;
	t_point	end;

	start.x = PLAYER_SIZE / 2;
	start.y = PLAYER_SIZE / 2;
	draw_filled_circle(cub3d.player.img, start, PLAYER_SIZE / 2, PLAYER_COLOR);
	end.x = start.x + cos(cub3d.player.angle) * PLAYER_SIZE / 2;
	end.y = start.y + sin(cub3d.player.angle) * PLAYER_SIZE / 2;
	draw_line(cub3d.player.img, start, end, DIR_LINE_COLOR);
}