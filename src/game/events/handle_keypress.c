
#include "cub3d.h"

static void	toggle_rays(t_cub3d *cub3d)
{
	if (cub3d->map.minimap_visible)
		cub3d->ray_caster.rays_visible = !cub3d->ray_caster.rays_visible;
	if (!cub3d->ray_caster.rays_visible)
		clear_image(cub3d->ray_caster.img);
}

static void	toggle_minimap(t_cub3d *cub3d)
{
	cub3d->map.minimap_visible = !cub3d->map.minimap_visible;
	cub3d->ray_caster.rays_visible = false;
	if (!cub3d->map.minimap_visible)
		clear_image(cub3d->map.img);
}

void handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_cub3d *cub3d;

	cub3d = (void *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		handle_close(param);
	if (keydata.key == MLX_KEY_TAB)
		toggle_minimap(cub3d);
	if (keydata.key == MLX_KEY_R)
		toggle_rays(cub3d);
}