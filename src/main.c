
#include "cub3d.h"


int main(int argc, char *argv[])
{
	t_cub3d	cub3d;

	if (argc != 2)
		handle_error("Invalid number of arguments");
	
	init_cub3d(&cub3d, argv[1]);
	print_grid(cub3d.map.grid);
	return (0);
}