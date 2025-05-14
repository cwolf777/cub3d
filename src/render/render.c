
#include "cub3d.h"

void	render_bg(t_cub3d *cub3d, uint32_t color)
{
	mlx_image_t	*bg;
	int			x;
	int			y;
	
	bg = mlx_new_image(cub3d->mlx, MAP_WIDTH, MAP_HEIGHT);
	if (!bg)
		handle_error("Failed to create background");
	y = 0;
	while(y < MAP_HEIGHT)
	{
		x = 0;
		while(x < MAP_WIDTH)
		{
			mlx_put_pixel(bg, x, y, color);
			x++;
		}
		y++;
	}
	if (mlx_image_to_window(cub3d->mlx, bg, 0, 0) < 0)
		handle_error("Failed to draw background");
}

void	render_player(t_cub3d *cub3d)
{
	t_point	start;
	t_point	end;
	int		x;
	int		y;

	if (cub3d->player_img)
	{
		mlx_delete_image(cub3d->mlx, cub3d->player_img);
		cub3d->player_img = NULL;
	}
	cub3d->player_img = mlx_new_image(cub3d->mlx, PLAYER_SIZE, PLAYER_SIZE);
	if (!cub3d->player_img)
		handle_error("Player image creation failed");

	y = 0;
	while (y < PLAYER_SIZE)
	{
		x = 0;
		while (x < PLAYER_SIZE)
		{
			mlx_put_pixel(cub3d->player_img, x, y, PLAYER_COLOR);
			x++;
		}
		y++;
	}
	start.x = PLAYER_SIZE / 2;
	start.y = PLAYER_SIZE / 2;
	end.x = start.x + cos(cub3d->player_angle) * PLAYER_SIZE / 2;
	end.y = start.y + sin(cub3d->player_angle) * PLAYER_SIZE / 2;
	draw_line(cub3d->player_img, start, end, 2, DIR_LINE_COLOR);
	if (mlx_image_to_window(cub3d->mlx, cub3d->player_img, cub3d->player_pos.x, cub3d->player_pos.y) < 0)
		handle_error("Failed to draw player");
}