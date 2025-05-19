
#include "cub3d.h"

void	convert(t_cub3d *cub3d)
{
	if (cub3d->player.orientation == 'W')
		cub3d->player.angle = degree_to_rad(180);
	if (cub3d->player.orientation == 'E')
		cub3d->player.angle = degree_to_rad(0);
	if (cub3d->player.orientation == 'N')
		cub3d->player.angle = degree_to_rad(90);
	if (cub3d->player.orientation == 'S')
		cub3d->player.angle = degree_to_rad(270);
	cub3d->player.pos.x = cub3d->player.pos.x * TILE_SIZE + PLAYER_SIZE / 2;
	cub3d->player.pos.y = cub3d->player.pos.y * TILE_SIZE + PLAYER_SIZE / 2;
}


int main(int argc, char *argv[])
{
	t_cub3d cub3d;
	if (argc != 2)
		handle_error("Invalid number of arguments");
	if (!validate_file_extension(argv[1], ".cub"))
		handle_error("File extension must be .cub");
	init_cub3d (&cub3d, argv[1]);
	print_cub3d_info(&cub3d);
	convert(&cub3d);
	render_bg(&cub3d, 0xFF000000);
	render_map(&cub3d);
	render_player(&cub3d);
	cub3d.ray_img = mlx_new_image(cub3d.mlx, 1280, 720);
	mlx_image_to_window(cub3d.mlx, cub3d.ray_img, 0, 0);
	// cast_rays(&cub3d);
	mlx_loop_hook(cub3d.mlx, player_controls, &cub3d);
	mlx_loop(cub3d.mlx);
	return (0);
}