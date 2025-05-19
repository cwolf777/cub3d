
#include "cub3d.h"

void handle_key_press(void *param)
{
	t_cub3d *cub3d;

	cub3d = (t_cub3d *)param;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
		move_forward(cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		move_backward(cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		rotate_left(cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		rotate_right(cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
		exit(EXIT_SUCCESS);	//todo
	render_player(cub3d);
	// cast_rays(cub3d);
}