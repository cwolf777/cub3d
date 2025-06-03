
#include "cub3d.h"


void cast_rays(t_cub3d *cub3d)
{
	int		i;
	t_point	start;
	t_ray	ray;
	t_point	hit_pos;
	double	start_angle;
	double	ray_angle;
	
	clear_image(cub3d->ray_caster.img);
	clear_image(cub3d->view_img);
	fill_background(cub3d);
	start_angle = cub3d->player.angle - (cub3d->player.fov / 2.0);
	i = 0;
	while (i < cub3d->ray_caster.num_rays)
	{
		ray_angle = start_angle + i * cub3d->ray_caster.angle_step;
		ray = cast_single_ray(cub3d, ray_angle);
		start = (t_point){MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2};
		hit_pos = world_to_minimap(cub3d, ray.hit_pos.x, ray.hit_pos.y);
		if (ray.is_vertical)
			draw_line(cub3d->ray_caster.img, start, hit_pos, 1, 0xFF0000FF);
		else
			draw_line(cub3d->ray_caster.img, start, hit_pos, 1, 0xFFFF00FF);
		render_wall_slice(cub3d, i, ray, ray_angle);
		i++;
	}
}

t_ray cast_single_ray(t_cub3d *cub3d, double ray_angle)
{
	t_ray hor_ray;
	t_ray ver_ray;
	
	hor_ray = cast_horizontal_ray(cub3d, ray_angle);
	ver_ray = cast_vertical_ray(cub3d, ray_angle);
	if (ver_ray.distance < hor_ray.distance)
		return (ver_ray);
	return (hor_ray);
}

t_ray cast_horizontal_ray(t_cub3d *cub3d, double ray_angle)
{
	t_ray ray;

	ray.is_vertical = false;
	double ray_dir_y = sin(ray_angle);
	int facing_up = ray_dir_y < 0;

	// Erste horizontale Gitterlinie berechnen
	double y_intercept = floor(cub3d->player.pixel_pos.y / TILE_SIZE) * TILE_SIZE;
	y_intercept += facing_up ? -0.0001 : TILE_SIZE;

	double x_intercept = cub3d->player.pixel_pos.x + (y_intercept - cub3d->player.pixel_pos.y) / tan(ray_angle);

	// Schrittgrößen
	double y_step = facing_up ? -TILE_SIZE : TILE_SIZE;
	double x_step = y_step / tan(ray_angle);

	double next_x = x_intercept;
	double next_y = y_intercept;

	// Gitter durchlaufen
	while (next_x >= 0 && next_x < cub3d->map.grid_width * TILE_SIZE &&
			next_y >= 0 && next_y < cub3d->map.grid_height * TILE_SIZE)
	{
		int map_x = (int)(next_x / TILE_SIZE);
		int map_y = (int)(next_y / TILE_SIZE);

		if (map_x >= 0 && map_y >= 0 &&
			cub3d->map.grid[map_y][map_x] == '1')
		{
			ray.hit_pos.x = next_x;
			ray.hit_pos.y = next_y;
			ray.distance = hypot(next_x - cub3d->player.pixel_pos.x, next_y - cub3d->player.pixel_pos.y);
			return ray;
		}

		next_x += x_step;
		next_y += y_step;
	}

	// Kein Treffer gefunden
	ray.distance = 1e30;
	return ray;
}

t_ray cast_vertical_ray(t_cub3d *cub3d, double ray_angle)
{
	t_ray ray;
	ray.is_vertical = 1;

	int facing_left = cos(ray_angle) < 0;

	double x_intercept = floor(cub3d->player.pixel_pos.x / TILE_SIZE) * TILE_SIZE;
	x_intercept += facing_left ? -0.0001 : TILE_SIZE;

	double y_intercept = cub3d->player.pixel_pos.y + (x_intercept - cub3d->player.pixel_pos.x) * tan(ray_angle);

	double x_step = facing_left ? -TILE_SIZE : TILE_SIZE;
	double y_step = x_step * tan(ray_angle);

	double next_x = x_intercept;
	double next_y = y_intercept;

	while (next_x >= 0 && next_x < cub3d->map.grid_width * TILE_SIZE &&
		next_y >= 0 && next_y < cub3d->map.grid_height * TILE_SIZE)
	{
		int map_x = (int)(next_x / TILE_SIZE);
		int map_y = (int)(next_y / TILE_SIZE);

		if (map_x >= 0 && map_y >= 0 &&
			cub3d->map.grid[map_y][map_x] == '1')
		{
			ray.hit_pos.x = next_x;
			ray.hit_pos.y = next_y;
			ray.distance = hypot(next_x - cub3d->player.pixel_pos.x, next_y - cub3d->player.pixel_pos.y);
			return ray;
		}

		next_x += x_step;
		next_y += y_step;
	}

	ray.distance = 1e30;
	return ray;
}
