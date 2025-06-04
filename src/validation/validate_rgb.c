
#include "cub3d.h"

void	validate_rgb(t_cub3d *cub3d, t_rgb rgb)
{
	if (rgb.red < 0 || rgb.red > 255)
		handle_close(cub3d, "Color code must be between 0 and 255");
	if (rgb.green < 0 || rgb.green > 255)
		handle_close(cub3d, "Color code must be between 0 and 255");
	if (rgb.blue < 0 || rgb.blue > 255)
		handle_close(cub3d, "Color code must be between 0 and 255");
}