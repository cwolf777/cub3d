
#include "cub3d.h"

void	init_window_size(t_cub3d *cub3d)
{
	cub3d->window_width = WINDOW_WIDTH;
	cub3d->window_height = WINDOW_HEIGHT;
}

static void	init_player(t_cub3d *cub3d)
{
	t_map		*map;
	t_player	*player;

	map = &cub3d->map;
	player = &cub3d->player;
	if (map->player_orientation == 'W')
		player->angle = convert_degree_to_rad(180);
	if (map->player_orientation == 'E')
		player->angle = convert_degree_to_rad(0);
	if (map->player_orientation == 'N')
		player->angle = convert_degree_to_rad(270);
	if (map->player_orientation == 'S')
		player->angle = convert_degree_to_rad(90);
	player->pixel_pos.x = (map->player_index.x * TILE_SIZE) + (TILE_SIZE / 2);
	player->pixel_pos.y = (map->player_index.y * TILE_SIZE) + (TILE_SIZE / 2);
	player->grid_pos.x = map->player_index.x;
	player->grid_pos.y = map->player_index.y;
	player->size = TILE_SIZE / 5;
	player->speed = 2;
	player->rot_speed = convert_degree_to_rad(5);
	player->fov = convert_degree_to_rad(60);
}

void	init_map(t_cub3d *cub3d)
{
	int		tile_width;
	int		tile_height;

	cub3d->minimap_img_width = cub3d->window_width / 5;
	cub3d->minimap_img_height = cub3d->window_height / 5;

	if (cub3d->minimap_img_width < MINIMAP_WIDTH)
		cub3d->minimap_img_width = MINIMAP_WIDTH;
	if (cub3d->minimap_img_height < MINIMAP_HEIGHT)
		cub3d->minimap_img_height = MINIMAP_HEIGHT;
	tile_width = cub3d->minimap_img_width / cub3d->map.grid_width;
	tile_height = cub3d->minimap_img_height / cub3d->map.grid_height;
	cub3d->map.tile_size = (int)fmin(tile_width, tile_height);
	if (cub3d->map.tile_size < TILE_SIZE)
		cub3d->map.tile_size = TILE_SIZE;
	cub3d->map.width = cub3d->map.tile_size * cub3d->map.grid_width;
	cub3d->map.height = cub3d->map.tile_size * cub3d->map.grid_height;
}

void	init_ray_caster(t_cub3d *cub3d)
{
	cub3d->ray_caster.num_rays = cub3d->window_width;
	cub3d->ray_caster.angle_step = cub3d->player.fov / cub3d->ray_caster.num_rays;
	cub3d->ray_caster.dist_proj_plane = (cub3d->window_width / 2.0) / tan(cub3d->player.fov / 2.0);
}

void	init_cub3d(t_cub3d *cub3d, char *path)
{
	cub3d->fd = -1;
	setup_mlx(cub3d);
	init_window_size(cub3d);
	parse_cub3d(cub3d, path);
	validate_cub3d(*cub3d);
	init_map(cub3d);
	init_player(cub3d);
	init_ray_caster(cub3d);
	create_view(cub3d);
	create_minimap(cub3d);
	set_layer_order(cub3d);
}

