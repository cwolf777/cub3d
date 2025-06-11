
#include "cub3d.h"

static bool	check_collision(t_map map, double px, double py)
{
	int i;
	double check_x;
	double check_y;
	int grid_x;
	int grid_y;

	i = 0;
	while(i < 360)
	{
		check_x = px + cos(degree_to_rad(i)) * PLAYER_SIZE * 1.3;
		check_y = py + sin(degree_to_rad(i)) * PLAYER_SIZE * 1.3;
		grid_x = (int)(check_x / TILE_SIZE);
		grid_y = (int)(check_y / TILE_SIZE);
		if (grid_y < 0 || grid_y >= map.grid_height || grid_x < 0 || grid_x >= map.grid_width)
		{
			i += 30;
			continue;
		}
		if (map.grid[grid_y][grid_x] == '1')
			return (true);
		i += 30;
	}
	return (false);
}

static void move_forward(t_cub3d *cub3d,double *move_x, double *move_y, double delta_time)
{
	*move_x += cos(cub3d->player.angle) * PLAYER_SPEED * delta_time;
	*move_y += sin(cub3d->player.angle) * PLAYER_SPEED * delta_time;
}
static void move_backward(t_cub3d *cub3d,double *move_x, double *move_y, double delta_time)
{
	*move_x -= cos(cub3d->player.angle) * PLAYER_SPEED * delta_time;
	*move_y -= sin(cub3d->player.angle) * PLAYER_SPEED * delta_time;
}
static void move_left(t_cub3d *cub3d,double *move_x, double *move_y, double delta_time)
{
	*move_x += cos(cub3d->player.angle - M_PI_2) * PLAYER_SPEED * delta_time;
	*move_y += sin(cub3d->player.angle - M_PI_2) * PLAYER_SPEED * delta_time;
}
static void move_right(t_cub3d *cub3d,double *move_x, double *move_y, double delta_time)
{
	*move_x += cos(cub3d->player.angle + M_PI_2) * PLAYER_SPEED * delta_time;
	*move_y += sin(cub3d->player.angle + M_PI_2) * PLAYER_SPEED * delta_time;
}

static void rotate_left(t_cub3d *cub3d, double delta_time)
{
	cub3d->player.angle -= PLAYER_ROT_SPEED * delta_time;
	if (cub3d->player.angle < 0)
		cub3d->player.angle += 2 * M_PI;
}

static void	rotate_right(t_cub3d *cub3d, double delta_time)
{
	cub3d->player.angle += PLAYER_ROT_SPEED * delta_time;
	if (cub3d->player.angle > 2 * M_PI)
		cub3d->player.angle -= 2 * M_PI;
}

static double get_elapsed_time(void)
{
	static double last_frame_time = 0.0;
	double current_time;
	double delta_time;
	current_time = mlx_get_time();
	if (last_frame_time == 0.0)
		last_frame_time = current_time;
	delta_time = current_time - last_frame_time;
	last_frame_time = current_time;
	if (delta_time > 0.05)
		delta_time = 0.05;
	return (delta_time);
}

void	update_player_pos(t_cub3d *cub3d, double new_x, double new_y)
{
	if (!check_collision(cub3d->map, new_x, new_y))
	{
		cub3d->player.pixel_pos.x = new_x;
		cub3d->player.pixel_pos.y = new_y;
	}
	else if (!check_collision(cub3d->map, new_x, cub3d->player.pixel_pos.y))
		cub3d->player.pixel_pos.x = new_x;
	else if (!check_collision(cub3d->map, cub3d->player.pixel_pos.x, new_y))
		cub3d->player.pixel_pos.y = new_y;
	cub3d->map.player_index.x = (int)(cub3d->player.pixel_pos.x / TILE_SIZE);
	cub3d->map.player_index.y = (int)(cub3d->player.pixel_pos.y / TILE_SIZE);
}

void player_movement(t_cub3d *cub3d)
{
	double	delta_time;
	double	move_x;
	double	move_y;

	delta_time = get_elapsed_time();
	move_x = 0.0;
	move_y = 0.0;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
		move_forward(cub3d, &move_x, &move_y, delta_time);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		move_backward(cub3d, &move_x, &move_y, delta_time);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		move_left(cub3d, &move_x, &move_y, delta_time);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		move_right(cub3d, &move_x, &move_y, delta_time);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
		rotate_left(cub3d, delta_time);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
		rotate_right(cub3d, delta_time);
	update_player_pos(cub3d, cub3d->player.pixel_pos.x + move_x, cub3d->player.pixel_pos.y + move_y);
}
