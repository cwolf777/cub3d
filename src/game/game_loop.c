
#include "cub3d.h"

void	game_loop(void *param)
{
	t_cub3d *cub3d;

	cub3d = (t_cub3d *)param;
	player_movement(cub3d);
	update_player_img_pos(cub3d);
	draw_map(*cub3d);
	draw_player(cub3d);
	// cast_rays(cub3d);
}
