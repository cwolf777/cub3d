
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

void	print_rgb(const char *label, t_rgb color)
{
	printf("  %s: [%d,%d,%d]\n", label, color.red, color.green, color.blue);
}

void	print_cub3d_info(t_cub3d *cub)
{
	printf("=========== CUB3D INFO ===========\n");
	printf("Graphics:\n");
	printf("    North: %s\n", cub->graphics.north.path);
	printf("    South: %s\n", cub->graphics.south.path);
	printf("    East:  %s\n", cub->graphics.east.path);
	printf("    West:  %s\n", cub->graphics.west.path);
	print_rgb("Floor Color", cub->graphics.floor);
	print_rgb("Ceiling Color", cub->graphics.ceiling);
	printf("Player:\n");
	printf("  x:  %d\n", cub->player.pos.x);
	printf("  y:  %d\n", cub->player.pos.y);
	printf("  orient:  %c\n", cub->player.orientation);
	printf("Map:\n");
	printf("  Width:  %d\n", cub->map.width);
	printf("  Height: %d\n", cub->map.height);
	printf("  Grid:\n");
	print_grid(cub->map.grid);

	printf("=========== END INFO ============\n");
}