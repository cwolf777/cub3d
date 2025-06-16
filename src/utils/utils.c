
#include "cub3d.h"

char	**copy_grid(t_cub3d *cub3d, t_map map)
{
	char	**new_grid;
	int		i;

	i = 0;
	new_grid = malloc(sizeof(char *) * (map.grid_height + 1));
	if (!new_grid)
		handle_error(cub3d, "Malloc failed in func: copy_map");
	while (map.grid[i] != NULL)
	{
		new_grid[i] = ft_strdup(map.grid[i]);
		if (!new_grid[i])
			handle_error(cub3d, "Malloc failed in func: copy_map");
		i++;
	}
	new_grid[i] = NULL;
	return (new_grid);
}


