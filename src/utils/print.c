
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

	printf("Map:\n");
	printf("  Width:  %d\n", cub->map.width);
	printf("  Height: %d\n", cub->map.height);
	printf("  Grid:\n");
	printf("Graphics:\n");
	printf("  Textures:\n");
	printf("    North: %p\n", (void *)cub->graphics.north_img);
	printf("    South: %p\n", (void *)cub->graphics.south_img);
	printf("    East:  %p\n", (void *)cub->graphics.east_img);
	printf("    West:  %p\n", (void *)cub->graphics.west_img);

	print_rgb("Floor Color", cub->graphics.floor);
	print_rgb("Ceiling Color", cub->graphics.ceiling);

	printf("=========== END INFO ============\n");
}