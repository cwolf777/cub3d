#include "cub3d.h"

static void clear_image(mlx_image_t *img)
{
	for (uint32_t y = 0; y < img->height; y++)
	{
		for (uint32_t x = 0; x < img->width; x++)
		{
			mlx_put_pixel(img, x, y, 0x00000000); // Transparent
		}
	}
}


void cast_rays(t_cub3d *cub3d)
{
	int num_rays = WINDOW_WIDTH - MINIMAP_WIDTH; //anpassen
	double fov = 60.0 * (M_PI / 180.0); // z. B. 60 Grad
	double angle_step = fov / num_rays;
	double start_angle = cub3d->player.angle - (fov / 2.0);

	clear_image(cub3d->ray_img);
	clear_image(cub3d->view_img);
	
	for (int i = 0; i < num_rays; i++)
	{
		double ray_angle = start_angle + i * angle_step;
		t_ray_hit hit = cast_single_ray(cub3d, ray_angle);
		
		// 3D Wandhöhe berechnen & zeichnen
		// render_wall_slice(cub3d, i, hit);
		
		t_point start = {
			.x = (int)(PLAYER_RADIUS + cub3d->player.pos.x),
			.y = (int)(PLAYER_RADIUS + cub3d->player.pos.y)
		};
		t_point end = {
			.x = (int)(hit.hit.x),
			.y = (int)(hit.hit.y)
		};
		draw_line(cub3d->ray_img, start, end, 1, 0xFF0000FF);
		render_wall_slice(cub3d, i, hit, ray_angle);
	}
}

t_ray_hit cast_single_ray(t_cub3d *cub3d, double ray_angle)
{
	t_ray_hit hor_hit = cast_horizontal_ray(cub3d, ray_angle);
	t_ray_hit ver_hit = cast_vertical_ray(cub3d, ray_angle);

	if (ver_hit.distance < hor_hit.distance)
		return ver_hit;
	else
		return hor_hit;
}

t_ray_hit cast_horizontal_ray(t_cub3d *cub3d, double ray_angle)
{
	t_ray_hit hit;
	hit.is_vertical = 0;

	double ray_dir_y = sin(ray_angle);
	int facing_up = ray_dir_y < 0;

	// Erste horizontale Gitterlinie berechnen
	double y_intercept = floor(cub3d->player.pos.y / TILE_SIZE) * TILE_SIZE;
	y_intercept += facing_up ? -0.0001 : TILE_SIZE;

	double x_intercept = cub3d->player.pos.x + (y_intercept - cub3d->player.pos.y) / tan(ray_angle);

	// Schrittgrößen
	double y_step = facing_up ? -TILE_SIZE : TILE_SIZE;
	double x_step = y_step / tan(ray_angle);

	double next_x = x_intercept;
	double next_y = y_intercept;

	// Gitter durchlaufen
	while (next_x >= 0 && next_x < cub3d->map.width * TILE_SIZE &&
		   next_y >= 0 && next_y < cub3d->map.height * TILE_SIZE)
	{
		int map_x = (int)(next_x / TILE_SIZE);
		int map_y = (int)(next_y / TILE_SIZE);

		if (map_x >= 0 && map_y >= 0 &&
			cub3d->map.grid[map_y][map_x] == '1')
		{
			hit.hit.x = next_x;
			hit.hit.y = next_y;
			hit.distance = hypot(next_x - cub3d->player.pos.x, next_y - cub3d->player.pos.y);
			return hit;
		}

		next_x += x_step;
		next_y += y_step;
	}

	// Kein Treffer gefunden
	hit.distance = 1e30;
	return hit;
}

t_ray_hit cast_vertical_ray(t_cub3d *cub3d, double ray_angle)
{
	t_ray_hit hit;
	hit.is_vertical = 1;

	int facing_left = cos(ray_angle) < 0;

	double x_intercept = floor(cub3d->player.pos.x / TILE_SIZE) * TILE_SIZE;
	x_intercept += facing_left ? -0.0001 : TILE_SIZE;

	double y_intercept = cub3d->player.pos.y + (x_intercept - cub3d->player.pos.x) * tan(ray_angle);

	double x_step = facing_left ? -TILE_SIZE : TILE_SIZE;
	double y_step = x_step * tan(ray_angle);

	double next_x = x_intercept;
	double next_y = y_intercept;

	while (next_x >= 0 && next_x < cub3d->map.width * TILE_SIZE &&
		   next_y >= 0 && next_y < cub3d->map.height * TILE_SIZE)
	{
		int map_x = (int)(next_x / TILE_SIZE);
		int map_y = (int)(next_y / TILE_SIZE);

		if (map_x >= 0 && map_y >= 0 &&
			cub3d->map.grid[map_y][map_x] == '1')
		{
			hit.hit.x = next_x;
			hit.hit.y = next_y;
			hit.distance = hypot(next_x - cub3d->player.pos.x, next_y - cub3d->player.pos.y); //?????
			return hit;
		}

		next_x += x_step;
		next_y += y_step;
	}

	hit.distance = 1e30;
	return hit;
}
