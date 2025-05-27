
#include "cub3d.h"

void clear_image(mlx_image_t *img)
{
	int	y;
	int	x;

	y = 0;
	while (y < (int)img->height)
	{
		x = 0;
		while (x < (int)img->width)
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

	start.x = PLAYER_SIZE / 2;
	start.y = PLAYER_SIZE / 2;
	draw_filled_circle(cub3d->player.img, start, PLAYER_SIZE / 2, PLAYER_COLOR);
	end.x = start.x + cos(cub3d->player.angle) * PLAYER_SIZE / 2;
	end.y = start.y + sin(cub3d->player.angle) * PLAYER_SIZE / 2;
	draw_line(cub3d->player.img, start, end, 1, DIR_LINE_COLOR);
}

void	fill_tile(t_map map, int start_x, int start_y, uint32_t color)
{
	int	pixel_x;
	int	pixel_y;
	int	x;
	int	y;
	
	y = 0;
	while (y < TILE_SIZE - 1)
	{
		x = 0;
		while (x < TILE_SIZE - 1)
		{
			pixel_x = x + start_x;
			pixel_y = y + start_y;
			if (pixel_x >= 0 && pixel_x < (int)map.img->width && pixel_y >= 0 && pixel_y < (int)map.img->height)
				mlx_put_pixel(map.img, pixel_x, pixel_y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_cub3d cub3d)
{
	int			x;
	int			y;
	int			off_set_x;
	int			off_set_y;

	clear_image(cub3d.map.img);
	off_set_x = cub3d.player.pixel_pos.x - MINIMAP_WIDTH / 2;
	off_set_y = cub3d.player.pixel_pos.y - MINIMAP_HEIGHT / 2;
	y = 0;
	while(y < cub3d.map.grid_height)
	{
		x = 0;
		while (x < cub3d.map.grid_width)
		{
			if (cub3d.map.grid[y][x] == '1')
				fill_tile(cub3d.map, x * TILE_SIZE - off_set_x, y * TILE_SIZE - off_set_y, GREEN);
			else
			fill_tile(cub3d.map, x * TILE_SIZE - off_set_x, y * TILE_SIZE - off_set_y, WHITE);
			x++;
		}
		y++;
	}
	draw_img_outline(cub3d.map.img, 2, PLAYER_COLOR);
}

void draw_img_outline(mlx_image_t *img, int line_width, uint32_t color)
{
	t_point	start;
	t_point	end;

	// Top edge
	start = (t_point){line_width, line_width};
	end = (t_point){img->width - line_width, line_width};
	draw_line(img, start, end, line_width, color);

	// Left edge
	start = (t_point){line_width, line_width};
	end = (t_point){line_width, img->height - line_width};
	draw_line(img, start, end, line_width, color);

	// Right edge
	start = (t_point){img->width - line_width, line_width};
	end = (t_point){img->width - line_width, img->height - line_width};
	draw_line(img, start, end, line_width, color);

	// Bottom edge
	start = (t_point){line_width, img->height - line_width};
	end = (t_point){img->width - line_width, img->height - line_width};
	draw_line(img, start, end, line_width, color);
}

