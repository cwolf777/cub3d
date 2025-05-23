
#include "cub3d.h"

void clear_image(mlx_image_t *img)
{
	int	y;
	int	x;

	y = 0;
	while (y < (int)img->height)
	{
		x = 0;
		while (x <(int) img->width)
		{
			mlx_put_pixel(img, x, y, 0x00000000); // Transparent
			x++;
		}
		y++;
	}
}

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
	if (start.x < end.x)
		sx = 1;
	else
		sx = -1;
	if (start.y < end.y)
		sy = 1;
	else
		sy = -1;
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


	start.x = cub3d->player.size / 2;
	start.y = cub3d->player.size / 2;
	draw_filled_circle(cub3d->player.img, start, cub3d->player.size / 2, PLAYER_COLOR);
	end.x = start.x + cos(cub3d->player.angle) * cub3d->player.size / 2;
	end.y = start.y + sin(cub3d->player.angle) * cub3d->player.size / 2;
	draw_line(cub3d->player.img, start, end, 1, DIR_LINE_COLOR);
}

void	fill_tile(t_map map, int start_x, int start_y, uint32_t color)
{
	int	pixel_x;
	int	pixel_y;

	pixel_y = 0;
	while (pixel_y < map.tile_size - 1)
	{
		pixel_x = 0;
		while (pixel_x < map.tile_size - 1)
		{
			if (pixel_x >= 0 && pixel_x < (int)map.img->width && pixel_y >= 0 && pixel_y < (int)map.img->height)
				mlx_put_pixel(map.img, start_x + pixel_x, start_y + pixel_y, color);
			pixel_x++;
		}
		pixel_y++;
	}
}

void	draw_map(t_map map)
{
	uint32_t	fill_color;
	int			x;
	int			y;
	char		tile;

	y = 0;
	while(y < MINIMAP_VIEW_SIZE)
	{
		x = 0;
		while (x < MINIMAP_VIEW_SIZE)
		{
			tile = map.grid[y][x];
			if (tile == '1')
				fill_color = 0xFFFF3333;
			else if (tile == '0')
				fill_color = 0xFFFFFFFF;
			else if (tile == 'N' || tile == 'S' || tile == 'W' || tile == 'E')
				fill_color = 0xFFFFFFFF;
			printf("x:%d, y:%d\n", x * map.tile_size, y * map.tile_size);
			fill_tile(map, x + map.player_pos.x * map.tile_size, y + map.player_pos.y * map.tile_size, fill_color);
			x++;
		}
		y++;
	}
}
