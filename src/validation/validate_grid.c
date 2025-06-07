
#include "cub3d.h"

void	flood_fill(char **grid, int x, int y)
{
	if (grid[y][x] == '1' || grid[y][x] == 'X')
		return ;
	if (ft_strchr("\t\n\v\f\r ", grid[y][x]))
		handle_error("Found exit");
	grid[y][x] = 'X';
	flood_fill(grid, x + 1, y);
	flood_fill(grid, x - 1, y);
	flood_fill(grid, x, y + 1);
	flood_fill(grid, x, y - 1);
}

void	validate_chars(char **grid)
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
				handle_error("Wrong chars in grid");
			j++;
		}
		i++;
	}
}

void	validate_grid(t_cub3d cub3d)
{
	char	**copy;

	validate_chars(cub3d.map.grid);
	copy = copy_grid(cub3d.map);
	flood_fill(copy, cub3d.map.player_index.x, cub3d.map.player_index.y);
	free_grid(copy);
}
