
#include "cub3d.h"

void	handle_error(t_cub3d *cub3d, char *error_msg)
{
	ft_printf("Error\n");
	ft_printf("%s\n", error_msg);
	if (cub3d)
		free_cub3d(cub3d);
	exit(EXIT_FAILURE);
}