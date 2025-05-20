#include "cub3d.h"

void render_wall_slice(t_cub3d *cub3d, int col, t_ray_hit hit, double ray_angle)
{
	double corrected_distance = hit.distance * cos(ray_angle - cub3d->player.angle);

	// Konstanten für Projektion 
	double fov = 60.0 * (M_PI / 180.0);
	double dist_proj_plane = (WINDOW_WIDTH / 2.0) / tan(fov / 2.0);

	double wall_height = (TILE_SIZE / corrected_distance) * dist_proj_plane;

	int wall_top = (WINDOW_HEIGHT / 2) - (wall_height / 2);
	int wall_bottom = (WINDOW_HEIGHT / 2) + (wall_height / 2);

	// Begrenzen auf sichtbaren Bereich
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom > WINDOW_HEIGHT)
		wall_bottom = WINDOW_HEIGHT;

	while (wall_top < wall_bottom)
	{
		int draw_x = col + MINIMAP_WIDTH; //rechts neben minimap
	
		if (draw_x >= 0 && draw_x < (int)cub3d->view_img->width &&
			wall_top >= 0 && wall_top < (int)cub3d->view_img->height)
		{
			if (hit.is_vertical == 1)
				mlx_put_pixel(cub3d->view_img, draw_x, wall_top, 0xFFFFFFFF);
			else
				mlx_put_pixel(cub3d->view_img, draw_x, wall_top, 0x808080);
		}
	
		wall_top++;
	}
}