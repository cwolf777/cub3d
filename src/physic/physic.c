
#include "cub3d.h"

// void	calc_player_dimension(int	px, int py)
// {
	
// }

bool	check_collision(t_map map, int px, int py)
{
	int	y;
	int	x;

	x = px / TILE_SIZE;
	y = py / TILE_SIZE;
	
	printf("y:%d x:%d\n", y, x);
	if (y < 0 || y > map.height || x < 0 || x > map.width)
		return (true);
	printf("tile:%c\n", map.grid[y][x]);
	if (map.grid[y][x] == '1')
		return (true);
	return (false);
}

void player_controls(void *param)
{
	t_cub3d *cub3d = (t_cub3d *)param;
	int speed = 5;
	double rot_speed;
	int	tempx;
	int	tempy;
	
	rot_speed = degree_to_rad(5);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
	{
		tempx = cos(cub3d->player.angle) * speed + cub3d->player.pos.x;
		tempy = sin(cub3d->player.angle) * speed + cub3d->player.pos.y;
		if (check_collision(cub3d->map, tempx, tempy))
			return ;
		cub3d->player.pos.x = tempx;
		cub3d->player.pos.y = tempy;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
	{
		tempx = cub3d->player.pos.x - cos(cub3d->player.angle) * speed;
		tempy = cub3d->player.pos.y - sin(cub3d->player.angle) * speed;
		if (check_collision(cub3d->map, tempx, tempy))
			return ;
		cub3d->player.pos.x = tempx;
		cub3d->player.pos.y = tempy;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		cub3d->player.angle -= rot_speed;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		cub3d->player.angle += rot_speed;

	render_player(cub3d);
	// cast_ray(cub3d);
	// cast_rays(cub3d);
}

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

// 		double ray_x = cub3d->player.pos.x + PLAYER_SIZE / 2;
// 		double ray_y = cub3d->player.pos.y + PLAYER_SIZE / 2;
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