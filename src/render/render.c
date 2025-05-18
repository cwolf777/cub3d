
#include "cub3d.h"

void	fill_tile(mlx_image_t *map_img, int x, int y, uint32_t color)
{
	int	px;
	int	py;

	py = 0;
	while (py < TILE_SIZE - 1)
	{
		px = 0;
		while (px < TILE_SIZE - 1)
		{
			mlx_put_pixel(map_img, x + px, y + py, color);
			px++;
		}
		py++;
	}
}

void	render_map(t_cub3d *cub3d)
{
	uint32_t	fill_color;
	// uint32_t	outline_color;
	int			x;
	int			y;
	char		tile;

	// outline_color = 0xFF000000;
	cub3d->map_img = mlx_new_image(cub3d->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	y = 0;
	while(y < cub3d->map.height)
	{
		x = 0;
		while (x < cub3d->map.width)
		{
			tile = cub3d->map.grid[y][x];
			if (tile == '1')
				fill_color = 0xFFFF3333;
			else if (tile == '0')
				fill_color = 0xFFFFFFFF;
			else if (tile == 'N' || tile == 'S' || tile == 'W' || tile == 'E')
				fill_color = 0xFFFFFFFF;
			fill_tile(cub3d->map_img, x * TILE_SIZE, y * TILE_SIZE , fill_color);
			x++;
		}
		y++;
	}
	mlx_image_to_window(cub3d->mlx, cub3d->map_img, 0, 0);
}

void	render_bg(t_cub3d *cub3d, uint32_t color)
{
	mlx_image_t	*bg;
	int			x;
	int			y;
	
	bg = mlx_new_image(cub3d->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (!bg)
		handle_error("Failed to create background");
	y = 0;
	while(y < MINIMAP_HEIGHT)
	{
		x = 0;
		while(x < MINIMAP_WIDTH)
		{
			mlx_put_pixel(bg, x, y, color);
			x++;
		}
		y++;
	}
	if (mlx_image_to_window(cub3d->mlx, bg, 0, 0) < 0)
		handle_error("Failed to draw background");
}

void	render_player(t_cub3d *cub3d)
{
	t_point	start;
	t_point	end;
	int		x;
	int		y;

	if (cub3d->player_img)
	{
		mlx_delete_image(cub3d->mlx, cub3d->player_img);
		cub3d->player_img = NULL;
	}
	cub3d->player_img = mlx_new_image(cub3d->mlx, PLAYER_SIZE, PLAYER_SIZE);
	if (!cub3d->player_img)
		handle_error("Player image creation failed");

	y = 0;
	while (y < PLAYER_SIZE)
	{
		x = 0;
		while (x < PLAYER_SIZE)
		{
			mlx_put_pixel(cub3d->player_img, x, y, PLAYER_COLOR);
			x++;
		}
		y++;
	}
	start.x = PLAYER_SIZE / 2;
	start.y = PLAYER_SIZE / 2;
	end.x = start.x + cos(cub3d->player.angle) * PLAYER_SIZE / 2;
	end.y = start.y + sin(cub3d->player.angle) * PLAYER_SIZE / 2;
	draw_line(cub3d->player_img, start, end, 2, DIR_LINE_COLOR);
	if (mlx_image_to_window(cub3d->mlx, cub3d->player_img, cub3d->player.pos.x, cub3d->player.pos.y) < 0)
		handle_error("Failed to draw player");
}