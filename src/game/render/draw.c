
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

void	draw_map(t_cub3d cub3d)
{
	uint32_t	fill_color;
	int			x;
	int			y;
	char		tile;
	t_player	player;
	t_map		map;
	// t_point		start;
	// t_point		end;


	map = cub3d.map;
	player = cub3d.player;
	clear_image(map.img);
	y = map.player_index.y - MINIMAP_VIEW_SIZE;
	if (y < 0)
		y = 0;
	while(y < map.grid_height)
	{
		x = map.player_index.x - MINIMAP_VIEW_SIZE;
		if (x < 0)
			x = 0;
		while (x < map.grid_width)
		{
			int tile_screen_x = x * TILE_SIZE - (map.player_index.x - MINIMAP_VIEW_SIZE) * TILE_SIZE;
			int tile_screen_y = y * TILE_SIZE - (map.player_index.y - MINIMAP_VIEW_SIZE) * TILE_SIZE;
			if (tile_screen_x < 0)
				tile_screen_x = 0;
			if (tile_screen_y < 0)
				tile_screen_y = 0;
			tile = map.grid[y][x];
			if (tile == '1')
				fill_color = 0xFFFF3333;
			else
				fill_color = 0xFFFFFFFF;
			fill_tile(map, tile_screen_x, tile_screen_y, fill_color);
			x++;
		}
		y++;
	}
	draw_img_outline(map.img, 2, PLAYER_COLOR);
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

void	draw_map_centered(t_map map)
{
	clear_image(map.img);

	int center_x = MINIMAP_WIDTH / 2;
	int center_y = MINIMAP_HEIGHT / 2;

	int start_y = map.player_index.y - MINIMAP_VIEW_SIZE;
	int end_y   = map.player_index.y + MINIMAP_VIEW_SIZE;
	int start_x = map.player_index.x - MINIMAP_VIEW_SIZE;
	int end_x   = map.player_index.x + MINIMAP_VIEW_SIZE;

	for (int y = start_y; y < end_y; y++)
	{
		for (int x = start_x; x < end_x; x++)
		{
			if (y < 0 || x < 0 || y >= map.grid_height || x >= map.grid_width)
				continue;

			int tile_offset_x = x - map.player_index.x;
			int tile_offset_y = y - map.player_index.y;

			int draw_x = center_x + tile_offset_x * TILE_SIZE;
			int draw_y = center_y + tile_offset_y * TILE_SIZE;

			char tile = map.grid[y][x];
			uint32_t color = (tile == '1') ? 0xFFFF0000 : 0xFFFFFFFF;

			fill_tile(map, draw_x, draw_y, color);
		}
	}

	// Spieler in die Mitte setzen
	fill_tile(map, center_x, center_y, 0xFF00FF00);
}
