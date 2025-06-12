
#include "cub3d.h"

void handle_keypress(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		handle_close(param);
}