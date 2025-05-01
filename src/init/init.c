

#include "cub3d.h"


void	init_cub3d(t_cub3d *cub3d, char *path)
{
	int	fd;

	ft_memset(cub3d, 0, sizeof(t_cub3d));
	cub3d->mlx = mlx_init(1280, 720, "Cub3d", false);
	if (!cub3d->mlx)
		handle_error("MLX not initialized");
	fd = open(path, O_RDONLY);
		if (fd < 0)
			handle_error("Failed to open file");
	parse_graphics(cub3d, fd);
	parse_map(&cub3d->map, fd);
	close (fd);
}

