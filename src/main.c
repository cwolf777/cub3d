
#include "cub3d.h"

int main(int argc, char *argv[])
{
	t_cub3d	cub3d;

	if (argc != 2)
		handle_error("Invalid number of arguments");
	if (!validate_file_extension(argv[1], ".cub"))
		handle_error("File extension must be .cub");
	init_cub3d(&cub3d, argv[1]);
	print_cub3d_info(&cub3d);
	return (0);
}