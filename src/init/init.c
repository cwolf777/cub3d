

#include "cub3d.h"


void	init_cub3d(t_cub3d *cub3d, char *path)
{

	ft_memset(cub3d, 0, sizeof(t_cub3d));
	cub3d->mlx = mlx_init(1280, 720, "Cub3d", false);
	if (!cub3d->mlx)
		handle_error("MLX not initialized");
	parse_cub3d(cub3d, path);
	validate_cub3d(*cub3d);
}

