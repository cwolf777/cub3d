#include "cub3d.h"

// void	draw_map(t_cub3d *cub3d)
// {
// 	uint32_t fill_color;
// 	uint32_t outline_color = 0xFF000000;

// 	for (int y = 0; y < cub3d->map.height; y++)
// 	{
// 		for (int x = 0; x < cub3d->map.width; x++)
// 		{
// 			char tile = cub3d->map.grid[y][x];

// 			if (tile == '1')
// 				fill_color = 0xFFFF3333;
// 			else if (tile == '0')
// 				fill_color = 0xFFFFFFFF;
// 			else if (tile == 'N' || tile == 'S' || tile == 'W' || tile == 'E')
// 				fill_color = 0xFFFFFFFF;

// 			mlx_image_t *tile_img = mlx_new_image(cub3d->mlx, TILE_SIZE, TILE_SIZE);
// 			if (!tile_img)
// 				handle_error("Tile image creation failed");

// 			for (int ty = 0; ty < TILE_SIZE; ty++)
// 			{
// 				for (int tx = 0; tx < TILE_SIZE; tx++)
// 				{
// 					// Zeichne Rahmen (1 Pixel dick)
// 					if (tx == 0 || ty == 0 || tx == TILE_SIZE - 1 || ty == TILE_SIZE - 1)
// 						mlx_put_pixel(tile_img, tx, ty, outline_color);
// 					else
// 						mlx_put_pixel(tile_img, tx, ty, fill_color);
// 				}
// 			}

// 			if (mlx_image_to_window(cub3d->mlx, tile_img, x * TILE_SIZE, y * TILE_SIZE) < 0)
// 				handle_error("Failed to draw map tile");
// 		}
// 	}
// }

// void cast_ray(t_cub3d *cub3d)
// {
// 	if (!cub3d->ray_img)
// 		return;
	
// 	for (int y = 0; y < 720; y++)
// 	{
// 		for (int x = 0; x < 1280; x++)
// 		{
// 			mlx_put_pixel(cub3d->ray_img, x, y, 0x00000000);
// 		}
// 	}	

// 	// Startposition (Mitte des Players)
// 	double ray_x = cub3d->player_pos.x + PLAYER_SIZE / 2;
// 	double ray_y = cub3d->player_pos.y + PLAYER_SIZE / 2;

// 	// Richtung
// 	double angle = cub3d->player_angle;
// 	double dx = cos(angle);
// 	double dy = sin(angle);

// 	// Schrittgröße (je kleiner, desto präziser)
// 	double step = 1.0;
// 	int max_distance = 1000;  // Maximaler Strahlweg (in Pixel)

// 	for (int i = 0; i < max_distance; i++)
// 	{
// 		int map_x = (int)(ray_x / TILE_SIZE);
// 		int map_y = (int)(ray_y / TILE_SIZE);

// 		// // Boundscheck
// 		if (map_x < 0 || map_x >= cub3d->map.width || map_y < 0 || map_y >= cub3d->map.height)
// 			break;

// 		// // Wand getroffen?
// 		if (cub3d->map.grid[map_y][map_x] == '1')
// 			break;

// 		// Ray einen Schritt weiter
// 		ray_x += dx * step;
// 		ray_y += dy * step;

// 		// Optional: Pixel setzen, um Strahl zu zeigen
// 		if (cub3d->ray_img)
// 			mlx_put_pixel(cub3d->ray_img, (int)ray_x, (int)ray_y, 0xFFFFFF);
// 	}
// }


