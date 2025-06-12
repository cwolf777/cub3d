
#include "cub3d.h"

void	handle_close(void *param)
{
	t_cub3d *cub3d;

	cub3d = (t_cub3d *)param;
	mlx_terminate(cub3d->mlx);
	free_cub3d(cub3d);
	exit(EXIT_SUCCESS);
}

