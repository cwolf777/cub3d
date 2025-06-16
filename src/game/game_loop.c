
#include "cub3d.h"

void	game_loop(void *param)
{
	t_cub3d *cub3d;

	cub3d = (t_cub3d *)param;
	player_movement(cub3d);
	if (cub3d->map.minimap_visible)
		draw_minimap(*cub3d);
	render_3d(*cub3d);
}
