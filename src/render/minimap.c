#include "cub3d.h"

void	draw_background(t_cub3d *cub3d, uint32_t color)
{
	mlx_image_t *background = mlx_new_image(cub3d->mlx, 1280, 720);
	if (!background)
		handle_error("Failed to create background");

	for (int y = 0; y < 720; y++)
	{
		for (int x = 0; x < 1280; x++)
		{
			mlx_put_pixel(background, x, y, color);
		}
	}

	if (mlx_image_to_window(cub3d->mlx, background, 0, 0) < 0)
		handle_error("Failed to draw background");
}

void	render_player(t_cub3d *cub3d)
{
	int32_t	size = PLAYER_SIZE;
	uint32_t color = 0xFFAAAAAA;
	uint32_t line_color = 0x0000FF;  // Rot für Blickrichtung

	if (cub3d->player_img)
	{
		mlx_delete_image(cub3d->mlx, cub3d->player_img);
		cub3d->player_img = NULL;
	}
	cub3d->player_img = mlx_new_image(cub3d->mlx, size, size);
	if (!cub3d->player_img)
		handle_error("Player image creation failed");

	for (int y = 0; y < size; y++)
		for (int x = 0; x < size; x++)
			mlx_put_pixel(cub3d->player_img, x, y, color);
	
	// Mittelpunkt des Spielers
	int center_x = size / 2;
	int center_y = size / 2;

	// Richtung berechnen
	double angle = cub3d->player_angle;
	int line_len = 100;

	// int end_x = center_x + cos(angle) * line_len;
	// int end_y = center_y + sin(angle) * line_len;

	// Linie von Mitte zur Blickrichtung
	// Simple Bresenham oder hier einfach direkte Linie:
	for (int i = 0; i < line_len; i++)
	{
		int px = center_x + cos(angle) * i;
		int py = center_y + sin(angle) * i;
		if (px >= 0 && px < size && py >= 0 && py < size)
			mlx_put_pixel(cub3d->player_img, px, py, line_color);
	}

	if (mlx_image_to_window(cub3d->mlx, cub3d->player_img, cub3d->player_pos.x, cub3d->player_pos.y) < 0)
		handle_error("Failed to draw player");
}

void player_controls(void *param)
{
	t_cub3d *cub3d = (t_cub3d *)param;
	int speed = 5;
	double rot_speed = 0.100530964912;
	
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
	{
		cub3d->player_pos.x += cos(cub3d->player_angle) * speed;
		cub3d->player_pos.y += sin(cub3d->player_angle) * speed;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
	{
		cub3d->player_pos.x -= cos(cub3d->player_angle) * speed;
		cub3d->player_pos.y -= sin(cub3d->player_angle) * speed;		
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		cub3d->player_angle -= rot_speed;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		cub3d->player_angle += rot_speed;

	render_player(cub3d);
	// cast_ray(cub3d);
	cast_rays(cub3d);
}

void	draw_map(t_cub3d *cub3d)
{
	uint32_t fill_color;
	uint32_t outline_color = 0xFF000000;

	for (int y = 0; y < cub3d->map.height; y++)
	{
		for (int x = 0; x < cub3d->map.width; x++)
		{
			char tile = cub3d->map.grid[y][x];

			if (tile == '1')
				fill_color = 0xFFFF3333;
			else if (tile == '0')
				fill_color = 0xFFFFFFFF;
			else if (tile == 'N' || tile == 'S' || tile == 'W' || tile == 'E')
				fill_color = 0xFFFFFFFF; // Spielerposi auch weiss

			mlx_image_t *tile_img = mlx_new_image(cub3d->mlx, TILE_SIZE, TILE_SIZE);
			if (!tile_img)
				handle_error("Tile image creation failed");

			for (int ty = 0; ty < TILE_SIZE; ty++)
			{
				for (int tx = 0; tx < TILE_SIZE; tx++)
				{
					// Zeichne Rahmen (1 Pixel dick)
					if (tx == 0 || ty == 0 || tx == TILE_SIZE - 1 || ty == TILE_SIZE - 1)
						mlx_put_pixel(tile_img, tx, ty, outline_color);
					else
						mlx_put_pixel(tile_img, tx, ty, fill_color);
				}
			}

			if (mlx_image_to_window(cub3d->mlx, tile_img, x * TILE_SIZE, y * TILE_SIZE) < 0)
				handle_error("Failed to draw map tile");
		}
	}
}

void cast_ray(t_cub3d *cub3d)
{
	if (!cub3d->ray_img)
		return;
	
	for (int y = 0; y < 720; y++)
	{
		for (int x = 0; x < 1280; x++)
		{
			mlx_put_pixel(cub3d->ray_img, x, y, 0x00000000);
		}
	}	

	// Startposition (Mitte des Players)
	double ray_x = cub3d->player_pos.x + PLAYER_SIZE / 2;
	double ray_y = cub3d->player_pos.y + PLAYER_SIZE / 2;

	// Richtung
	double angle = cub3d->player_angle;
	double dx = cos(angle);
	double dy = sin(angle);

	// Schrittgröße (je kleiner, desto präziser)
	double step = 1.0;
	int max_distance = 1000;  // Maximaler Strahlweg (in Pixel)

	for (int i = 0; i < max_distance; i++)
	{
		int map_x = (int)(ray_x / TILE_SIZE);
		int map_y = (int)(ray_y / TILE_SIZE);

		// // Boundscheck
		if (map_x < 0 || map_x >= cub3d->map.width || map_y < 0 || map_y >= cub3d->map.height)
			break;

		// // Wand getroffen?
		if (cub3d->map.grid[map_y][map_x] == '1')
			break;

		// Ray einen Schritt weiter
		ray_x += dx * step;
		ray_y += dy * step;

		// Optional: Pixel setzen, um Strahl zu zeigen
		if (cub3d->ray_img)
			mlx_put_pixel(cub3d->ray_img, (int)ray_x, (int)ray_y, 0xFFFFFF);
	}
}


void cast_rays(t_cub3d *cub3d)
{
	if (!cub3d->ray_img)
		return;

	// Bild leeren
	for (int y = 0; y < 720; y++)
		for (int x = 0; x < 1280; x++)
			mlx_put_pixel(cub3d->ray_img, x, y, 0x00000000);

	int num_rays = 60;
	double fov = 60.0 * (M_PI / 180.0);  // 60 Grad in Bogenmaß
	double start_angle = cub3d->player_angle - (fov / 2.0);
	double angle_step = fov / num_rays;

	for (int r = 0; r < num_rays; r++)
	{
		double angle = start_angle + r * angle_step;
		double dx = cos(angle);
		double dy = sin(angle);

		double ray_x = cub3d->player_pos.x + PLAYER_SIZE / 2;
		double ray_y = cub3d->player_pos.y + PLAYER_SIZE / 2;
		double step = 1.0;
		int max_distance = 1000;

		for (int i = 0; i < max_distance; i++)
		{
			int map_x = (int)(ray_x / TILE_SIZE);
			int map_y = (int)(ray_y / TILE_SIZE);

			if (map_x < 0 || map_x >= cub3d->map.width || map_y < 0 || map_y >= cub3d->map.height)
				break;

			if (cub3d->map.grid[map_y][map_x] == '1')
				break;

			ray_x += dx * step;
			ray_y += dy * step;

			mlx_put_pixel(cub3d->ray_img, (int)ray_x, (int)ray_y, 0xFFFFFF);
		}
	}
}