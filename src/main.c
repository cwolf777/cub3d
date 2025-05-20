
#include "cub3d.h"


int main(int argc, char *argv[])
{
	t_cub3d cub3d;
	if (argc != 2)
		handle_error("Invalid number of arguments");
	if (!validate_file_extension(argv[1], ".cub"))
		handle_error("File extension must be .cub");
	init_cub3d (&cub3d, argv[1]);
	print_cub3d_info(&cub3d);
	// render_bg(&cub3d, 0xFF000000);
	render_map(&cub3d);
	render_player(&cub3d);
	cub3d.ray_img = mlx_new_image(cub3d.mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (!cub3d.ray_img)
		handle_error("Failed to create ray image");
	if (mlx_image_to_window(cub3d.mlx, cub3d.ray_img, 0, 0) < 0)
		handle_error("Failed to show ray image");
	//3D
	cub3d.view_img = mlx_new_image(cub3d.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub3d.view_img)
		handle_error("Failed to create 3D view image");
	mlx_image_to_window(cub3d.mlx, cub3d.view_img, 0, 0);
	mlx_key_hook(cub3d.mlx, handle_keypress, &cub3d);
	mlx_close_hook(cub3d.mlx, handle_close, &cub3d);
	mlx_loop_hook(cub3d.mlx, game_loop, &cub3d);
	mlx_loop(cub3d.mlx);
	mlx_terminate(cub3d.mlx);
	return (0);
}