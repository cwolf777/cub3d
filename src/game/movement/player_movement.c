
#include "cub3d.h"

static bool	check_collision(t_map map, int px, int py)
{
	int	y;
	int	x;

	x = px / TILE_SIZE;
	y = py / TILE_SIZE;
	
	if (y < 0 || y > map.height || x < 0 || x > map.width)
		return (true);
	if (map.grid[y][x] == '1')
		return (true);
	return (false);
}

void	move_forward(t_cub3d *cub3d)
{
	int	tempx;
	int	tempy;

	tempx = cos(cub3d->player.angle) * PLAYER_SPEED + cub3d->player.pos.x;
	tempy = sin(cub3d->player.angle) * PLAYER_SPEED + cub3d->player.pos.y;
	if (check_collision(cub3d->map, tempx, tempy))
		return ;
	cub3d->player.pos.x = tempx;
	cub3d->player.pos.y = tempy;
}

void	move_backward(t_cub3d *cub3d)
{
	int	tempx;
	int	tempy;

	tempx = cub3d->player.pos.x - cos(cub3d->player.angle) * PLAYER_SPEED;
	tempy = cub3d->player.pos.y - sin(cub3d->player.angle) * PLAYER_SPEED;
	if (check_collision(cub3d->map, tempx, tempy))
		return ;
	cub3d->player.pos.x = tempx;
	cub3d->player.pos.y = tempy;
}

void	rotate_left(t_cub3d *cub3d)
{
	cub3d->player.angle -= PLAYER_ROT_SPEED;
}
void	rotate_right(t_cub3d *cub3d)
{
	cub3d->player.angle += PLAYER_ROT_SPEED;
}