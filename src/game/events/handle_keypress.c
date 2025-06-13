
#include "cub3d.h"

void handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_cub3d *cub3d;

	cub3d = (void *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		handle_close(param);
	if (keydata.key == MLX_KEY_TAB)
		cub3d->map.show_map = !cub3d->map.show_map;
	if (keydata.key == MLX_KEY_R)
		cub3d->ray_caster.show_rays = !cub3d->ray_caster.show_rays;
}