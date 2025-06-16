
#include "cub3d.h"

// void render_player(t_cub3d *cub3d)
// {
// 	int	img_x;
// 	int	img_y;

// 	cub3d->player.img = mlx_new_image(cub3d->mlx, PLAYER_SIZE, PLAYER_SIZE);
// 	if (!cub3d->player.img)
// 		handle_error(cub3d, "Player image creation failed");
// 	draw_player(*cub3d);
// 	img_x = cub3d->map.width / 2 - PLAYER_SIZE / 2;
// 	img_y = cub3d->map.height / 2 - PLAYER_SIZE / 2;
// 	if (mlx_image_to_window(cub3d->mlx, cub3d->player.img, img_x, img_y) < 0)
// 		handle_error(cub3d, "Failed to draw player");
// }

void	render_minimap(t_cub3d *cub3d)
{
	cub3d->map.img = mlx_new_image(cub3d->mlx, cub3d->map.width , cub3d->map.height);
	if (!cub3d->map.img)
		handle_error(cub3d, "Failed to load map_img");
	// if (cub3d->map.show_map)
	// 	draw_minimap(*cub3d);
	mlx_image_to_window(cub3d->mlx, cub3d->map.img, 0, 0);
	cub3d->ray_caster.img = mlx_new_image(cub3d->mlx, cub3d->map.width , cub3d->map.height);
	if (!cub3d->ray_caster.img)
		handle_error(cub3d, "Failed to create ray_caster image");
	mlx_image_to_window(cub3d->mlx, cub3d->ray_caster.img, 0, 0);
}


