
#include "cub3d.h"

void update_minimap_size(t_cub3d *cub3d)
{
	cub3d->map.width = cub3d->window_width / 5;
	cub3d->map.height = cub3d->window_height / 5;
}

void	handle_resize(int width, int height, void *param)
{
	t_cub3d *cub3d;

	cub3d = (void *)param;
	mlx_delete_image(cub3d->mlx, cub3d->view_img);
	mlx_delete_image(cub3d->mlx, cub3d->map.img);
	mlx_delete_image(cub3d->mlx, cub3d->ray_caster.img);
	cub3d->view_img = mlx_new_image(cub3d->mlx, width, height);
	cub3d->window_height = height;
	cub3d->window_width = width;
	update_minimap_size(cub3d);
	render_minimap(cub3d);
	init_ray_caster(cub3d);
	mlx_image_to_window(cub3d->mlx, cub3d->view_img, 0 ,0);
}
