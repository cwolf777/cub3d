
#include "cub3d.h"

static void	parse_img(t_img *img, mlx_t *mlx, char *path)
{
	skip_whitespace(&path);
	init_img(img, mlx, path);
}

void	load_texture(t_cub3d *cub3d, int *seen_flags, char *str)
{
	char *temp;
	
	temp = str + 2;
	if (ft_strncmp("NO", str, ft_strlen("NO")) == 0 && str[2] != '\0' && is_white_space(str[2]))
	{
		parse_img(&cub3d->graphics.north, cub3d->mlx, temp);
		seen_flags[NO]++;
	}
	else if (ft_strncmp("WE", str, ft_strlen("WE")) == 0 && str[2] != '\0' && is_white_space(str[2]))
	{
		parse_img(&cub3d->graphics.west, cub3d->mlx, temp);
		seen_flags[WE]++;
	}
	else if (ft_strncmp("EA", str, ft_strlen("EA")) == 0 && str[2] != '\0' && is_white_space(str[2]))
	{
		parse_img(&cub3d->graphics.east, cub3d->mlx, temp);
		seen_flags[EA]++;
	}
	else if (ft_strncmp("SO", str, ft_strlen("SO")) == 0 && str[2] != '\0' && is_white_space(str[2]))
	{
		parse_img(&cub3d->graphics.south, cub3d->mlx, temp);
		seen_flags[SO]++;
	}
}
