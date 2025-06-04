
#include "cub3d.h"

void	parse_cub3d(t_cub3d *cub3d, char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
		if (fd < 0)
			handle_close(cub3d, "Failed to open file");
	parse_graphics(cub3d, fd);
	parse_map(cub3d, &cub3d->map, fd); 
	close(fd);
}
