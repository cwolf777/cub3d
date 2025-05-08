
#include "cub3d.h"

static void	parse_img(t_img *img, mlx_t *mlx, char *path)
{
	skip_whitespace(&path);
	init_img(img, mlx, path);
}

void	load_texture(t_cub3d *cub3d, int *seen_flags, char *str)
{
	if (ft_strncmp(str, "NO", 2) == 0)
	{
		parse_img(&cub3d->graphics.north, cub3d->mlx, str + 2);
		seen_flags[NO]++;
	}
	else if (ft_strncmp(str, "WE", 2) == 0)
	{
		parse_img(&cub3d->graphics.west, cub3d->mlx, str + 2);
		seen_flags[WE]++;
	}
	else if (ft_strncmp(str, "EA", 2) == 0)
	{
		parse_img(&cub3d->graphics.east, cub3d->mlx, str + 2);
		seen_flags[EA]++;
	}
	else if (ft_strncmp(str, "SO", 2) == 0)
	{
		parse_img(&cub3d->graphics.south, cub3d->mlx, str + 2);
		seen_flags[SO]++;
	}
}
