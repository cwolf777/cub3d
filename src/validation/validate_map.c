
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

bool	validate_chars(char **grid)
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
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

void	validate_grid(char **grid)
{
	if (!validate_chars(grid))
	{
		// free_map(grid);
		handle_error("Grid chars wrong");
	}
}