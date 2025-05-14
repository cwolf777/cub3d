
#include "cub3d.h"


int main(int argc, char *argv[])
{
	t_cub3d cub3d;
	if (argc != 2)
		handle_error("Invalid number of arguments");
	if (!validate_file_extension(argv[1], ".cub"))
		handle_error("File extension must be .cub");
	init_cub3d (&cub3d, argv[1]);
	cub3d.player_pos.x = 300;
	cub3d.player_pos.y = 500;

	cub3d.player_angle = 0.0; //schaut nach rechts
	print_cub3d_info(&cub3d);
	render_bg(&cub3d, 0xFF000000);
	draw_map(&cub3d);
	render_player(&cub3d);
	cub3d.ray_img = mlx_new_image(cub3d.mlx, 1280, 720);
	if (!cub3d.ray_img)
		handle_error("Failed to create ray image");
	if (mlx_image_to_window(cub3d.mlx, cub3d.ray_img, 0, 0) < 0)
		handle_error("Failed to show ray image");
	// cast_rays(&cub3d);
	mlx_loop_hook(cub3d.mlx, player_controls, &cub3d);
	mlx_loop(cub3d.mlx);
	return (0);
}