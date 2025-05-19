
#include "cub3d.h"

// bool	check_collision(t_map map, int px, int py)
// {
// 	int	y;
// 	int	x;

// 	x = px / TILE_SIZE;
// 	y = py / TILE_SIZE;
	
// 	if (y < 0 || y > map.height || x < 0 || x > map.width)
// 		return (true);
// 	if (map.grid[y][x] == '1')
// 		return (true);
// 	return (false);
// }



// void cast_rays(t_cub3d *cub3d)
// {
// 	if (!cub3d->ray_img)
// 		return;

// 	// Bild leeren
// 	for (int y = 0; y < 720; y++)
// 		for (int x = 0; x < 1280; x++)
// 			mlx_put_pixel(cub3d->ray_img, x, y, 0x00000000);

// 	int num_rays = 60;
// 	double fov = 60.0 * (M_PI / 180.0);  // 60 Grad in Bogenmaß
// 	double start_angle = cub3d->player.angle - (fov / 2.0);
// 	double angle_step = fov / num_rays;

// 	for (int r = 0; r < num_rays; r++)
// 	{
// 		double angle = start_angle + r * angle_step;
// 		double dx = cos(angle);
// 		double dy = sin(angle);

// 		double ray_x = cub3d->player.pos.x;
// 		double ray_y = cub3d->player.pos.y;
// 		double step = 1.0;
// 		int max_distance = 1000;

// 		for (int i = 0; i < max_distance; i++)
// 		{
// 			int map_x = (int)(ray_x / TILE_SIZE);
// 			int map_y = (int)(ray_y / TILE_SIZE);

// 			if (map_x < 0 || map_x >= cub3d->map.width || map_y < 0 || map_y >= cub3d->map.height)
// 				break;

// 			if (cub3d->map.grid[map_y][map_x] == '1')
// 				break;

// 			ray_x += dx * step;
// 			ray_y += dy * step;

// 			mlx_put_pixel(cub3d->ray_img, (int)ray_x, (int)ray_y, 0xFFFFFF);
// 		}
// 	}
// }