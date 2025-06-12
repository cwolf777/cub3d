

#include "cub3d.h"

void	init_ray_caster(t_cub3d *cub3d)
{
	cub3d->ray_caster.num_rays = WINDOW_WIDTH;
	cub3d->ray_caster.angle_step = cub3d->player.fov / cub3d->ray_caster.num_rays;
	cub3d->ray_caster.img = mlx_new_image(cub3d->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	cub3d->ray_caster.dist_proj_plane = (WINDOW_WIDTH / 2.0) / tan(cub3d->player.fov / 2.0);
	if (!cub3d->ray_caster.img)
		handle_error(cub3d, "Failed to create 3D view image");
}

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
		player->angle = degree_to_rad(270);
	if (map->player_orientation == 'S')
		player->angle = degree_to_rad(90);
	player->pixel_pos.x = (map->player_index.x * TILE_SIZE) + (TILE_SIZE / 2);
	player->pixel_pos.y = (map->player_index.y * TILE_SIZE) + (TILE_SIZE / 2);
	player->grid_pos.x = map->player_index.x;
	player->grid_pos.y = map->player_index.y;
	player->size = TILE_SIZE / 5;
	player->speed = 2;
	player->rot_speed = degree_to_rad(5);
	player->fov = degree_to_rad(60);
}

// static void	init_map(t_cub3d *cub3d)
// {
// 	int		tile_width;
// 	int		tile_height;

// 	// tile_height = MINIMAP_HEIGHT / cub3d->map.grid_height;
// 	// tile_width = MINIMAP_WIDTH / cub3d->map.grid_width;
// 	// cub3d->map.tile_size = tile_width;
// 	// if (tile_height < tile_width)
// 	// 	cub3d->map.tile_size = tile_height;
// 	// if (cub3d->map.tile_size < 2)
// 	// 	cub3d->map.tile_size = 2;
// 	cub3d->map.pixel_width = cub3d->map.tile_size * cub3d->map.grid_width;
// 	cub3d->map.pixel_height = cub3d->map.tile_size * cub3d->map.grid_height;
// }

void	init_cub3d(t_cub3d *cub3d, char *path)
{
	cub3d->fd = -1;
	cub3d->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", false);
	if (!cub3d->mlx)
		handle_error(cub3d, "MLX not initialized");
	parse_cub3d(cub3d, path);
	validate_cub3d(*cub3d);
	// init_map(cub3d);
	init_player(cub3d);
	init_ray_caster(cub3d);
	cub3d->view_img = mlx_new_image(cub3d->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub3d->view_img)
		handle_error(cub3d, "Failed to create 3D view image");
	mlx_image_to_window(cub3d->mlx, cub3d->view_img, 0, 0);
}

