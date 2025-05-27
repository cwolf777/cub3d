#include "cub3d.h"

void render_wall_slice(t_cub3d *cub3d, int col, t_ray_hit hit, double ray_angle)
{
	double corrected_distance = hit.distance * cos(ray_angle - cub3d->player.angle);

	// Konstanten für Projektion 
	double fov = 60.0 * (M_PI / 180.0);
	double dist_proj_plane = (WINDOW_WIDTH / 2.0) / tan(fov / 2.0);

	double wall_height = (cub3d->map.tile_size / corrected_distance) * dist_proj_plane;

	int wall_top = (WINDOW_HEIGHT / 2) - (wall_height / 2);
	int wall_bottom = (WINDOW_HEIGHT / 2) + (wall_height / 2);

	// Begrenzen auf sichtbaren Bereich
	// if (wall_top < 0)
	// 	wall_top = 0;
	// if (wall_bottom > WINDOW_HEIGHT)
	// 	wall_bottom = WINDOW_HEIGHT;

	// === 1. TEXTUR ERMITTELN ===
	mlx_image_t *texture = NULL;
	if (hit.is_vertical)
	{
		if (cos(ray_angle) < 0)
			texture = cub3d->graphics.west.img;
		else
			texture = cub3d->graphics.east.img;
	}
	else
	{
		if (sin(ray_angle) < 0)
			texture = cub3d->graphics.north.img;
		else

			texture = cub3d->graphics.south.img;
	}
	if (!texture) return;

	// === 2. TEXTUR-X berechnen ===
	int tex_x;
	if (hit.is_vertical)
	{
		int y_within_tile = (int)hit.hit.y % cub3d->map.tile_size;
		tex_x = y_within_tile;
	}
	else
	{
		int x_within_tile = (int)hit.hit.x % cub3d->map.tile_size;
		tex_x = x_within_tile;
	}

	// Skalieren auf Texturbreite
	tex_x = tex_x * (texture->width / cub3d->map.tile_size);

	int y = wall_top;
	while (y < wall_bottom)
	{
		int draw_x = col + MINIMAP_WIDTH;
	
		// Bildschirmgrenzen prüfen
		if (draw_x >= 0 && draw_x < (int)cub3d->view_img->width &&
			y >= 0 && y < (int)cub3d->view_img->height)
		{
			// Y-Position innerhalb der Wand berechnen
			double wall_y_ratio = (double)(y - wall_top) / (wall_bottom - wall_top);
			int tex_y = wall_y_ratio * texture->height;
	
			// Pixel aus Textur lesen
			uint32_t *tex_pixels = (uint32_t *)texture->pixels;
			uint32_t color = tex_pixels[tex_y * texture->width + tex_x];
	
			// Pixel auf Bild setzen
			mlx_put_pixel(cub3d->view_img, draw_x, y, color);
		}
		y++;
	}
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
				if (x >= 0 && x < (int)cub3d->view_img->width &&
				y >= 0 && y < (int)cub3d->view_img->height)
					mlx_put_pixel(cub3d->view_img, x, y, floor_color);
			}
			else
			{
				if (x >= 0 && x < (int)cub3d->view_img->width &&
				y >= 0 && y < (int)cub3d->view_img->height)
					mlx_put_pixel(cub3d->view_img, x, y, ceiling_color);
			}
			x++;
		}
		y++;
	}
}