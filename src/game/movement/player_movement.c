
#include "cub3d.h"

static bool	check_collision(t_map map, int px, int py, int tile_size)
{
	int i;
	int check_x;
	int check_y;
	int grid_x;
	int grid_y;

	i = 0;
	while(i < 360)
	{
		check_x = px + cos(degree_to_rad(i)) * PLAYER_SIZE;
		check_y = py + sin(degree_to_rad(i)) * PLAYER_SIZE;
		grid_x = check_x / tile_size;
		grid_y = check_y / tile_size;
		if (grid_y < 0 || grid_y >= map.grid_height || grid_x < 0 || grid_x >= map.grid_width)
		{
			i += 15;
			continue;
		}
		if (map.grid[grid_y][grid_x] == '1')
			return (true);
		i += 15;
	}
	return (false);
}

static void	move_forward(t_cub3d *cub3d)
{
	int dx; 
	int dy;
	int new_x;
	int new_y;

	dx = cos(cub3d->player.angle) * PLAYER_SPEED;
	dy = sin(cub3d->player.angle) * PLAYER_SPEED;
	new_x = cub3d->player.pixel_pos.x + dx;
	new_y = cub3d->player.pixel_pos.y + dy;
	if (!check_collision(cub3d->map, new_x, cub3d->player.pixel_pos.y, TILE_SIZE))
		cub3d->player.pixel_pos.x = new_x;
	if (!check_collision(cub3d->map, cub3d->player.pixel_pos.x, new_y, TILE_SIZE))
		cub3d->player.pixel_pos.y = new_y;
}

static void	move_backward(t_cub3d *cub3d)
{
	int dx; 
	int dy;
	int new_x;
	int new_y;

	dx = cos(cub3d->player.angle) * PLAYER_SPEED;
	dy = sin(cub3d->player.angle) * PLAYER_SPEED;
	new_x = cub3d->player.pixel_pos.x - dx;
	new_y = cub3d->player.pixel_pos.y - dy;
	if (!check_collision(cub3d->map, new_x, cub3d->player.pixel_pos.y, TILE_SIZE))
		cub3d->player.pixel_pos.x = new_x;
	if (!check_collision(cub3d->map, cub3d->player.pixel_pos.x, new_y, TILE_SIZE))
		cub3d->player.pixel_pos.y = new_y;
}

static void	move_left(t_cub3d *cub3d)
{
	int dx; 
	int dy;
	int new_x;
	int new_y;

	dx = cos(cub3d->player.angle - M_PI_2) * PLAYER_SPEED;
	dy = sin(cub3d->player.angle - M_PI_2) * PLAYER_SPEED;
	new_x = cub3d->player.pixel_pos.x + dx;
	new_y = cub3d->player.pixel_pos.y + dy;
	if (!check_collision(cub3d->map, new_x, cub3d->player.pixel_pos.y, TILE_SIZE))
		cub3d->player.pixel_pos.x = new_x;
	if (!check_collision(cub3d->map, cub3d->player.pixel_pos.x, new_y, TILE_SIZE))
		cub3d->player.pixel_pos.y = new_y;
}
static void	move_right(t_cub3d *cub3d)
{
	int dx; 
	int dy;
	int new_x;
	int new_y;

	dx = cos(cub3d->player.angle + M_PI_2) * PLAYER_SPEED;
	dy = sin(cub3d->player.angle + M_PI_2) * PLAYER_SPEED;
	new_x = cub3d->player.pixel_pos.x + dx;
	new_y = cub3d->player.pixel_pos.y + dy;
	if (!check_collision(cub3d->map, new_x, cub3d->player.pixel_pos.y, TILE_SIZE))
		cub3d->player.pixel_pos.x = new_x;
	if (!check_collision(cub3d->map, cub3d->player.pixel_pos.x, new_y, TILE_SIZE))
		cub3d->player.pixel_pos.y = new_y;
}


static void rotate_left(t_cub3d *cub3d)
{
	cub3d->player.angle -= PLAYER_ROT_SPEED;
	if (cub3d->player.angle < 0)
		cub3d->player.angle += 2 * M_PI;
}

static void	rotate_right(t_cub3d *cub3d)
{
	cub3d->player.angle += PLAYER_ROT_SPEED;
	if (cub3d->player.angle > 2 * M_PI)
		cub3d->player.angle -= 2 * M_PI;
}

void	player_movement(t_cub3d *cub3d)
{
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
		move_forward(cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		move_backward(cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		move_left(cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		move_right(cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
		rotate_left(cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
		rotate_right(cub3d);
	cub3d->map.player_index.x = cub3d->player.pixel_pos.x / TILE_SIZE;
	cub3d->map.player_index.y = cub3d->player.pixel_pos.y / TILE_SIZE;
}

