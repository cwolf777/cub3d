
#include "cub3d.h"

void	handle_close(t_cub3d *cub3d, char *error_msg)
{
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
	if (cub3d->map.grid)
	{
		while(cub3d->map.grid[i])
		{
			free(cub3d->map.grid[i]);
			i++;
		}
		free(cub3d->map.grid);
	}
	if (cub3d->graphics.north.path)
		free(cub3d->graphics.north.path);
	if (cub3d->graphics.south.path)
		free(cub3d->graphics.south.path);
	if (cub3d->graphics.west.path)
		free(cub3d->graphics.west.path);
	if (cub3d->graphics.east.path)
		free(cub3d->graphics.east.path);
	//mlx termiante maybe
	exit(EXIT_FAILURE);
}

void	handle_close_cb(void *param)
{
	handle_close((t_cub3d *)param, "Window closed");
}