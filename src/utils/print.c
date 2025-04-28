
#include "cub3d.h"

void	print_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i] != NULL)
	{
		ft_printf("%s\n", grid[i]);
		i++;
	}
}