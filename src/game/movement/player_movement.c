
#include "cub3d.h"

static bool	check_collision(t_map map, int px, int py, int tile_size)
{
	int	y;
	int	x;

	x = px / tile_size;
	y = py / tile_size;
	
	if (y < 0 || y > map.grid_height || x < 0 || x > map.grid_width)
		return (true);
	if (map.grid[y][x] == '1')
		return (true);
	return (false);
}

static void	move_forward(t_cub3d *cub3d)
{
	int	tempx;
	int	tempy;

	// tempx = cub3d->player.pixel_pos.x + cos(cub3d->player.angle) * (cub3d->player.speed + cub3d->player.size);
	// tempy = cub3d->player.pixel_pos.y + sin(cub3d->player.angle) * (cub3d->player.speed + cub3d->player.size);
	tempx = cub3d->player.pixel_pos.x + cos(cub3d->player.angle) * cub3d->player.speed;
	tempy = cub3d->player.pixel_pos.y + sin(cub3d->player.angle) * cub3d->player.speed;
	if (check_collision(cub3d->map, tempx, tempy, cub3d->map.tile_size))
		return ;
	cub3d->player.pixel_pos.x = cub3d->player.pixel_pos.x + cos(cub3d->player.angle) * cub3d->player.speed;
	cub3d->player.pixel_pos.y = cub3d->player.pixel_pos.y + sin(cub3d->player.angle) * cub3d->player.speed;
}

static void	move_backward(t_cub3d *cub3d)
{
	int	tempx;
	int	tempy;

	// tempx = cub3d->player.pixel_pos.x - cos(cub3d->player.angle) * (cub3d->player.speed + cub3d->player.size);
	// tempy = cub3d->player.pixel_pos.y - sin(cub3d->player.angle) * (cub3d->player.speed + cub3d->player.size);
	tempx = cub3d->player.pixel_pos.x - cos(cub3d->player.angle) * cub3d->player.speed;
	tempy = cub3d->player.pixel_pos.y - sin(cub3d->player.angle) * cub3d->player.speed;
	if (check_collision(cub3d->map, tempx, tempy, cub3d->map.tile_size))
		return ;
	cub3d->player.pixel_pos.x = cub3d->player.pixel_pos.x - cos(cub3d->player.angle) * cub3d->player.speed;
	cub3d->player.pixel_pos.y = cub3d->player.pixel_pos.y - sin(cub3d->player.angle) * cub3d->player.speed;
}

static void	rotate_left(t_cub3d *cub3d)
{
	cub3d->player.angle -= cub3d->player.rot_speed;
}
static void	rotate_right(t_cub3d *cub3d)
{
	cub3d->player.angle += cub3d->player.rot_speed;
}

void	player_movement(t_cub3d *cub3d)
{
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
		move_forward(cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		move_backward(cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		rotate_left(cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		rotate_right(cub3d);
	cub3d->map.player_pos.x = cub3d->player.pixel_pos.x / cub3d->map.tile_size;
	cub3d->map.player_pos.y = cub3d->player.pixel_pos.y / cub3d->map.tile_size;
}

