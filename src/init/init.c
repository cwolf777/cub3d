

#include "cub3d.h"

static void	init_player(t_cub3d *cub3d)
{
	if (cub3d->map.player_orientation == 'W')
		cub3d->player.angle = degree_to_rad(180);
	if (cub3d->map.player_orientation == 'E')
		cub3d->player.angle = degree_to_rad(0);
	if (cub3d->map.player_orientation == 'N')
		cub3d->player.angle = degree_to_rad(90);
	if (cub3d->map.player_orientation == 'S')
		cub3d->player.angle = degree_to_rad(270);
	cub3d->player.pos.x = cub3d->map.player_idx.x * TILE_SIZE + PLAYER_RADIUS;
	cub3d->player.pos.y = cub3d->map.player_idx.y * TILE_SIZE + PLAYER_RADIUS;
}

void	init_cub3d(t_cub3d *cub3d, char *path)
{
	ft_memset(cub3d, 0, sizeof(t_cub3d));
	cub3d->mlx = mlx_init(1280, 720, "Cub3d", false);
	if (!cub3d->mlx)
		handle_error("MLX not initialized");
	parse_cub3d(cub3d, path);
	validate_cub3d(*cub3d);
	init_player(cub3d);
}

