
#include "cub3d.h"

int main(int argc, char *argv[])
{
	t_cub3d cub3d;

	ft_memset(&cub3d, 0, sizeof(t_cub3d));
	if (argc != 2)
		handle_error(&cub3d, "Invalid number of arguments");
	if (!validate_file_extension(argv[1], ".cub"))
		handle_error(&cub3d, "File extension must be .cub");
	init_cub3d(&cub3d, argv[1]);
	print_cub3d_info(&cub3d);
	render_map(&cub3d);
	render_player(&cub3d);
	mlx_image_to_window(cub3d.mlx, cub3d.ray_caster.img, 0, 0);
	mlx_key_hook(cub3d.mlx, handle_keypress, &cub3d);
	mlx_close_hook(cub3d.mlx, handle_close, &cub3d);
	mlx_loop_hook(cub3d.mlx, game_loop, &cub3d);
	mlx_loop(cub3d.mlx);
	// mlx_terminate(cub3d.mlx);
	return (EXIT_SUCCESS);
}
