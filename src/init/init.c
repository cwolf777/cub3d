

#include "cub3d.h"

static void	init_player(t_cub3d *cub3d)
{
	t_map		*map;
	t_player	*player;

	map = &cub3d->map;
	player = &cub3d->player;
	if (map->player_orientation == 'W')
		player->angle = degree_to_rad(180);
	if (map->player_orientation == 'E')
		player->angle = degree_to_rad(0);
	if (map->player_orientation == 'N')
		player->angle = degree_to_rad(90);
	if (map->player_orientation == 'S')
		player->angle = degree_to_rad(270);
	player->pos.x = map->player_idx.x * map->tile_size + map->tile_size / 2;
	player->pos.y = map->player_idx.y * map->tile_size + map->tile_size / 2;
	player->size = cub3d->map.tile_size / 5;
	player->speed = cub3d->map.tile_size * 0.1;
	player->rot_speed = degree_to_rad(5);
}

static void	init_map(t_cub3d *cub3d)
{
	int		tile_width;
	int		tile_height;

	tile_height = MINIMAP_HEIGHT / cub3d->map.height;
	tile_width = MINIMAP_WIDTH / cub3d->map.width;
	cub3d->map.tile_size = tile_width;
	if (tile_height < tile_width)
		cub3d->map.tile_size = tile_height;
}

void	init_cub3d(t_cub3d *cub3d, char *path)
{
	ft_memset(cub3d, 0, sizeof(t_cub3d));
	cub3d->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", false);
	if (!cub3d->mlx)
		handle_error("MLX not initialized");
	parse_cub3d(cub3d, path);
	validate_cub3d(*cub3d);
	init_map(cub3d);
	init_player(cub3d);
}

