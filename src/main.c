
#include "cub3d.h"


mlx_texture_t *load_texture(const char *path) {
    mlx_texture_t *texture = mlx_load_png(path);  // Falls du PNGs lädst
    if (!texture)
        handle_error("Failed to load texture");
    return texture;
}

int main(int argc, char *argv[])
{
	t_cub3d cub3d;

	if (argc != 2)
	handle_error("Invalid number of arguments");
	if (!validate_file_extension(argv[1], ".cub"))
	handle_error("File extension must be .cub");

	char *test_map[] = {
		"1111111111111111111",
		"1W11001001001000001",
		"1011000001000001001",
		"1001001001111101111",
		"1001111000001001001",
		"1000000000000001001",
		"1001111111111001001",
		"1111000000000001011",
		"1000000001000000001",
		"1111111111111111111",
		NULL
	};
	cub3d.map.grid = test_map;
	cub3d.map.height = 10;
	cub3d.map.width = 19;
	cub3d.mlx = mlx_init(1280, 720, "Cub3d", false);
	
	cub3d.graphics.north.path = "./textures/north.png";
	cub3d.graphics.south.path = "./textures/south.png";
	cub3d.graphics.west.path = "./textures/west.png";
	cub3d.graphics.east.path = "./textures/east.png";
	
	mlx_texture_t *north_texture = load_texture("./textures/north.png");
	cub3d.graphics.north.img = mlx_texture_to_image(cub3d.mlx, north_texture);
	
	mlx_texture_t *south_texture = load_texture("./textures/south.png");
	cub3d.graphics.south.img = mlx_texture_to_image(cub3d.mlx, south_texture);
	
	mlx_texture_t *west_texture = load_texture("./textures/west.png");
	cub3d.graphics.west.img = mlx_texture_to_image(cub3d.mlx, west_texture);
	
	mlx_texture_t *east_texture = load_texture("./textures/east.png");
	cub3d.graphics.east.img = mlx_texture_to_image(cub3d.mlx, east_texture);
	
	cub3d.graphics.floor = (t_rgb){220, 220, 220};  // Beispiel für Bodenfarbe
	cub3d.graphics.ceiling = (t_rgb){10, 10, 10};  // Beispiel für Deckenfarbe

	cub3d.player_pos.x = 300;
	cub3d.player_pos.y = 500;
	cub3d.player_angle = 0.0; //schaut nach rechts
	
	draw_background(&cub3d, 0xFF000000);
	draw_map(&cub3d);
	render_player(&cub3d);

	cub3d.ray_img = mlx_new_image(cub3d.mlx, 1280, 720);
	if (!cub3d.ray_img)
		handle_error("Failed to create ray image");

	if (mlx_image_to_window(cub3d.mlx, cub3d.ray_img, 0, 0) < 0)
		handle_error("Failed to show ray image");
	// cast_ray(&cub3d);
	cast_rays(&cub3d);
	mlx_loop_hook(cub3d.mlx, player_controls, &cub3d);
	mlx_loop(cub3d.mlx);
	// init_cub3d(&cub3d, argv[1]);
	print_cub3d_info(&cub3d);
	return (0);
}

// int main(int argc, char *argv[])
// {
// 	t_cub3d	cub3d;

// 	if (argc != 2)
// 		handle_error("Invalid number of arguments");
// 	if (!validate_file_extension(argv[1], ".cub"))
// 		handle_error("File extension must be .cub");
// 	init_cub3d(&cub3d, argv[1]);
// 	// print_cub3d_info(&cub3d);


// 	mlx_loop(cub3d.mlx);
// 	return (0);
// }