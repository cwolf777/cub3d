
#include "cub3d.h"

void	render_map(t_cub3d *cub3d)
{
	cub3d->map.img = mlx_new_image(cub3d->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (!cub3d->map.img)
		handle_error("Failed to load map_img");
	draw_minimap(*cub3d);
	mlx_image_to_window(cub3d->mlx, cub3d->map.img, 0, 0);
	cub3d->ray_caster.img = mlx_new_image(cub3d->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (!cub3d->ray_caster.img)
		handle_error("Failed to create ray_caster image");
	mlx_image_to_window(cub3d->mlx, cub3d->ray_caster.img, 0, 0);
}

void render_player(t_cub3d *cub3d)
{
	int	img_x;
	int	img_y;

	cub3d->player.img = mlx_new_image(cub3d->mlx, PLAYER_SIZE, PLAYER_SIZE);
	if (!cub3d->player.img)
		handle_error("Player image creation failed");
	draw_player(cub3d);
	img_x = MINIMAP_WIDTH / 2 - PLAYER_SIZE / 2;
	img_y = MINIMAP_HEIGHT / 2 - PLAYER_SIZE / 2;
	if (mlx_image_to_window(cub3d->mlx, cub3d->player.img, img_x, img_y) < 0)
		handle_error("Failed to draw player");
}

// void	render_bg(t_cub3d *cub3d, uint32_t color)
// {
// 	mlx_image_t	*bg;
// 	int			x;
// 	int			y;
	
// 	bg = mlx_new_image(cub3d->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
// 	if (!bg)
// 		handle_error("Failed to create background");
// 	y = 0;
// 	while(y < MINIMAP_HEIGHT)
// 	{
// 		x = 0;
// 		while(x < MINIMAP_WIDTH)
// 		{
// 			mlx_put_pixel(bg, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// 	if (mlx_image_to_window(cub3d->mlx, bg, 0, 0) < 0)
// 		handle_error("Failed to draw background");
// }