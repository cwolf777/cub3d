#include "cub3d.h"


void	init_render_buffer(t_cub3d *cub3d)
{
	cub3d->image_buffer = mlx_new_image(cub3d->mlx, 1280, 720);
	if (!cub3d->image_buffer)
		handle_error("Failed to create image");
	
	mlx_image_to_window(cub3d->mlx, cub3d->image_buffer, 0, 0);
}