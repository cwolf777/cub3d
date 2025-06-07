
#include "cub3d.h"

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