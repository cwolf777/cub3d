

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
	cub3d->player.pos.x = cub3d->map.player_idx.x * cub3d->tile_size + cub3d->tile_size / 2;
	cub3d->player.pos.y = cub3d->map.player_idx.y * cub3d->tile_size + cub3d->tile_size / 2;
}

void	init_cub3d(t_cub3d *cub3d, char *path)
{
	int		tile_width;
	int		tile_height;

	ft_memset(cub3d, 0, sizeof(t_cub3d));
	cub3d->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", false);
	if (!cub3d->mlx)
		handle_error("MLX not initialized");
	parse_cub3d(cub3d, path);
	validate_cub3d(*cub3d);
	tile_height = MINIMAP_HEIGHT / cub3d->map.height;
	tile_width = MINIMAP_WIDTH / cub3d->map.width;
	cub3d->tile_size = tile_width;
	if (tile_height < tile_width)
		cub3d->tile_size = tile_height;
	cub3d->player_size = cub3d->tile_size /5;
	printf("tile_size:%d \nplayer_size:%d\n", cub3d->tile_size, cub3d->player_size);
	init_player(cub3d);
}

