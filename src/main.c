
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

	char *test_map[] = {
		"1111111111111111111",
		"10W1001001001000001",
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
	if (argc != 2)
		handle_error("Invalid number of arguments");
	if (!validate_file_extension(argv[1], ".cub"))
		handle_error("File extension must be .cub");
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