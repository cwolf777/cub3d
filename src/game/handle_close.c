
#include "cub3d.h"

void	handle_close(void *param)
{
	t_cub3d *cub3d;

	cub3d = (t_cub3d *)param;
	get_next_line(-1);
	if (cub3d->fd != -1)
		close(cub3d->fd);
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
		free_grid(cub3d->map.grid);
	if (cub3d->graphics.north.path)
		free(cub3d->graphics.north.path);
	if (cub3d->graphics.south.path)
		free(cub3d->graphics.south.path);
	if (cub3d->graphics.west.path)
		free(cub3d->graphics.west.path);
	if (cub3d->graphics.east.path)
		free(cub3d->graphics.east.path);
	mlx_close_window(cub3d->mlx);
	// mlx_terminate(cub3d->mlx);
}

void	handle_error(t_cub3d *cub3d, char *error_msg)
{
	ft_printf("Error\n");
	ft_printf("%s\n", error_msg);
	if (cub3d)
		handle_close(cub3d);
	exit(EXIT_FAILURE);
}