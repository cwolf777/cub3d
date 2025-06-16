
#include "cub3d.h"

void	handle_resize(int width, int height, void *param)
{
	t_cub3d *cub3d;

	cub3d = (void *)param;
	mlx_delete_image(cub3d->mlx, cub3d->view_img);
	mlx_delete_image(cub3d->mlx, cub3d->map.img);
	mlx_delete_image(cub3d->mlx, cub3d->ray_caster.img);
	cub3d->window_height = height;
	cub3d->window_width = width;
	init_map(cub3d);
	init_ray_caster(cub3d);
	create_view(cub3d);
	create_minimap(cub3d);
	set_layer_order(cub3d);
}
