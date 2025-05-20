
#include "cub3d.h"

void	handle_close(void *param)
{
	t_cub3d *cub3d;

	cub3d = (t_cub3d *)param;
	mlx_delete_image(cub3d->mlx, cub3d->player_img);
	mlx_delete_image(cub3d->mlx, cub3d->ray_img);
	mlx_delete_image(cub3d->mlx, cub3d->map_img);
}