
#include "cub3d.h"

void	flood_fill(t_cub3d *cub3d, char **grid, int x, int y)
{
	if (x < 0 || x >= cub3d->map.grid_width || y < 0 || y >= cub3d->map.grid_height)
	{
		free_grid(grid);
		handle_close(cub3d, "Invalid Map");
	}
	if (grid[y][x] == '1' || grid[y][x] == 'X')
		return ;
	if (ft_strchr("\t\n\v\f\r ", grid[y][x]))
	{
		free_grid(grid);
		handle_close(cub3d, "Found exit");
	}
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
	flood_fill(cub3d, copy, cub3d->map.player_index.x, cub3d->map.player_index.y);
	free_grid(copy);
}
