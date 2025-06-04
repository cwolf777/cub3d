
#include "cub3d.h"

void	flood_fill(t_cub3d *cub3d, char **grid, int x, int y)
{
	if (grid[y][x] == '1' || grid[y][x] == 'X')
		return ;
	if (ft_strchr("\t\n\v\f\r ", grid[y][x]))
		handle_close(cub3d, "Found exit");
	grid[y][x] = 'X';
	flood_fill(cub3d, grid, x + 1, y);
	flood_fill(cub3d, grid, x - 1, y);
	flood_fill(cub3d, grid, x, y + 1);
	flood_fill(cub3d, grid, x, y - 1);
}

void	validate_chars(t_cub3d *cub3d, char **grid)
{
	int	i;
	int	j;

	i = 0;
	while (grid[i] != NULL)
	{
		j = 0;
		while (grid[i][j] != '\0')
		{
			if (!ft_strchr("01NSEW\t\n\v\f\r ", grid[i][j]))
				handle_close(cub3d, "Wrong chars in grid");
			j++;
		}
		i++;
	}
}

void	validate_grid(t_cub3d *cub3d)
{
	char	**copy;

	validate_chars(cub3d, cub3d->map.grid);
	copy = copy_grid(cub3d, cub3d->map);
	flood_fill(cub3d, copy, cub3d->player.grid_pos.x, cub3d->player.grid_pos.y);
	free_grid(copy);
}
