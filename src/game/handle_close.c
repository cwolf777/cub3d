
#include "cub3d.h"

void	handle_close(void *param, char *error_msg)
{
	t_cub3d *cub3d;

	cub3d = (t_cub3d *)param;
	int	i;

	i = 0;
	printf("Error: %s", error_msg);
	if (cub3d->player.img)
		mlx_delete_image(cub3d->mlx, cub3d->player.img);
	if (cub3d->ray_caster.img)
		mlx_delete_image(cub3d->mlx, cub3d->ray_caster.img);
	if (cub3d->map.img)
		mlx_delete_image(cub3d->mlx, cub3d->map.img);
	if (cub3d->view_img)
		mlx_delete_image(cub3d->mlx, cub3d->view_img);
	if (cub3d->graphics.north.img)
		mlx_delete_image(cub3d->mlx, cub3d->graphics.north.img);
	if (cub3d->graphics.south.img)
		mlx_delete_image(cub3d->mlx, cub3d->graphics.south.img);
	if (cub3d->graphics.west.img)
		mlx_delete_image(cub3d->mlx, cub3d->graphics.west.img);
	if (cub3d->graphics.east.img)
		mlx_delete_image(cub3d->mlx, cub3d->graphics.east.img);
	while(cub3d->map.grid[i])
	{
		free(cub3d->map.grid[i]);
		i++;
	}
	//if stamtments 
	free(cub3d->map.grid);
	free(cub3d->graphics.north.path);
	free(cub3d->graphics.south.path);
	free(cub3d->graphics.west.path);
	free(cub3d->graphics.east.path);
	//mlx termiante maybe
	exit(EXIT_FAILURE);
}