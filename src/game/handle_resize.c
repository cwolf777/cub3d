
#include "cub3d.h"

void	handle_resize(int width, int height, void *param)
{
	t_cub3d *cub3d;

	cub3d = (void *)param;
	mlx_delete_image(cub3d->mlx, cub3d->view_img);
	cub3d->view_img = mlx_new_image(cub3d->mlx, width, height);
	cub3d->window_height = height;
	cub3d->window_width = width;
	init_ray_caster(cub3d);
	mlx_image_to_window(cub3d->mlx, cub3d->view_img, 0 ,0);
}