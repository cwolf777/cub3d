
#include "cub3d.h"

void	parse_player(t_cub3d *cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub3d->map.height)
	{
		x = 0;
		while (x < cub3d->map.width)
		{
			if (ft_strchr("NWES", cub3d->map.grid[y][x]))
			{
				cub3d->player.pos.x = x;
				cub3d->player.pos.y = y;
				cub3d->player.orientation = cub3d->map.grid[y][x];
			
			}
			x++;
		}
		y++;
	}
}
