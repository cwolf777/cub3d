
#include "cub3d.h"

bool	check_collision(t_map map, int x, int y)
{
	if (map.grid[y][x] == '1')
		return (false);
	return (true);
}


void player_controls(void *param)
{
	t_cub3d *cub3d = (t_cub3d *)param;
	int speed = 5;
	double rot_speed;

	rot_speed = degree_to_rad(5);
	
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
	{
		cub3d->player.pos.x += cos(cub3d->player.angle) * speed;
		cub3d->player.pos.y += sin(cub3d->player.angle) * speed;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
	{
		cub3d->player.pos.x -= cos(cub3d->player.angle) * speed;
		cub3d->player.pos.y -= sin(cub3d->player.angle) * speed;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		cub3d->player.angle -= rot_speed;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		cub3d->player.angle += rot_speed;

	render_player(cub3d);
	// cast_ray(cub3d);
	cast_rays(cub3d);
}