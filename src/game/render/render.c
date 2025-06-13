
#include "cub3d.h"



void	render_3d(t_cub3d cub3d)
{
	clear_image(cub3d.ray_caster.img);
	draw_ceiling(cub3d);
	draw_floor(cub3d);
	ray_caster(cub3d);
}
