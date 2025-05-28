#include "cub3d.h"

mlx_image_t *get_wall_texture(t_cub3d *cub3d, t_ray ray, double ray_angle)
{
	if (ray.is_vertical)
	{
		if (cos(ray_angle) < 0)
			return (cub3d->graphics.west.img);
		else
			return (cub3d->graphics.east.img);
	}
	else
	{
		if (sin(ray_angle) < 0)
			return (cub3d->graphics.north.img);
		else
			return (cub3d->graphics.south.img);
	}
}


void render_wall_slice(t_cub3d *cub3d, int draw_x, t_ray ray, double ray_angle)
{
	double		corrected_distance;
	mlx_image_t	*wall_texture;
	int			offset_x;

	corrected_distance = ray.distance * cos(ray_angle - cub3d->player.angle);
	// Konstanten für Projektion
	double wall_height = (TILE_SIZE / corrected_distance) * cub3d->ray_caster.dist_proj_plane;
	int wall_top = (WINDOW_HEIGHT / 2) - (wall_height / 2);
	int wall_bottom = (WINDOW_HEIGHT / 2) + (wall_height / 2);

	wall_texture = get_wall_texture(cub3d, ray, ray_angle);

	// === 2. TEXTUR-X berechnen ===
	if (ray.is_vertical)
		offset_x = ray.hit_pos.y % TILE_SIZE;
	else
		offset_x = ray.hit_pos.x % TILE_SIZE;
	offset_x = offset_x *(wall_texture->width / TILE_SIZE);
	draw_wall(cub3d, wall_texture, draw_x, wall_top, offset_x, wall_bottom, wall_top);

}

void fill_background(t_cub3d *cub3d)
{
	int	y;
	int	x;
	uint32_t floor_color;
	uint32_t ceiling_color;

	floor_color = rgb_to_color(cub3d->graphics.floor);
	ceiling_color = rgb_to_color(cub3d->graphics.ceiling);
	y = 0;
	x = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (y < WINDOW_HEIGHT / 2)
			{
				if (x >= 0 && x < (int)cub3d->view_img->width && y >= 0 && y < (int)cub3d->view_img->height)
					mlx_put_pixel(cub3d->view_img, x, y, floor_color);
			}
			else
			{
				if (x >= 0 && x < (int)cub3d->view_img->width && y >= 0 && y < (int)cub3d->view_img->height)
					mlx_put_pixel(cub3d->view_img, x, y, ceiling_color);
			}
			x++;
		}
		y++;
	}
}