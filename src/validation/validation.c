
#include "cub3d.h"

bool	validate_file_extension(char *path, char *extension)
{
	int		i;
	int		j;
	char	*filename;

	filename = ft_strrchr(path, '/');
	if (!filename)
		filename = path;
	else
		filename++;
	i = ft_strlen(filename) - 1;
	j = ft_strlen(extension) - 1;
	if (i == j)
		return (false);
	while (j >= 0)
	{
		if (filename[i] != extension[j])
			return (false);
		i--;
		j--;
	}
	return (true);
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
			if (!ft_strchr("01NSEW", grid[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	validate_walls(char **grid)
{
	int	i;
	int	j;

	i = 0;
	while (grid[i] != NULL)
	{
		j = 0;
		while (grid[i][j] != '\0')
		{
			if ((i == 0 || grid[i + 1] == NULL) && grid[i][j] != '1')
				return (false);
			if ((j == 0 || grid[i][j + 1] == '\0') && grid[i][j] != '1')
				return (false);
			j++;
		} 
		i++;
	}
	return (true);
}

void	validate_grid(char **grid)
{
	if (!validate_walls(grid))
	{
		free_map(grid);
		handle_error("Grid walls wrong");
	}
	if (!validate_chars(grid))
	{
		free_map(grid);
		handle_error("Grid chars wrong");
	}
}

bool	validate_rgb(t_rgb rgb)
{
	if (rgb.red < 0 || rgb.red > 255)
		return (false);
	if (rgb.green < 0 || rgb.green > 255)
		return (false);
	if (rgb.blue < 0 || rgb.blue > 255)
		return (false);
	return (true);
}

// int	check_valid_pathway(t_game game)
// {
// 	int		exit;
// 	int		collectible;
// 	char	**copy;

// 	exit = 0;
// 	collectible = 0;
// 	copy = copy_map(game);
// 	flood_fill(copy, (t_point){game.player.x, game.player.y}, &exit, \
// 		&collectible);
// 	free_map(copy);
// 	if (exit != count_component(game.map, 'E')
// 		|| collectible != count_component(game.map, 'C'))
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }