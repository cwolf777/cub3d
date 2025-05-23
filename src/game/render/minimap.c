#include "cub3d.h"

// static void clear_image(mlx_image_t *img)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	while (y < (int)img->height)
// 	{
// 		x = 0;
// 		while (x <(int) img->width)
// 		{
// 			mlx_put_pixel(img, x, y, 0x00000000); // Transparent
// 			x++;
// 		}
// 		y++;
// 	}
// }


// void cast_rays(t_cub3d *cub3d)
// {
// 	int		i;
// 	t_point	start;
// 	t_ray	ray;
// 	double	ray_angle;
	
// 	clear_image(cub3d->ray_caster.img);
// 	// clear_image(cub3d->view_img);
// 	i = 0;
// 	while (i < cub3d->ray_caster.num_rays)
// 	{
// 		ray_angle = cub3d->ray_caster.start_angle + i * cub3d->ray_caster.angle_step;
// 		ray = cast_single_ray(cub3d, ray_angle);
// 		// render_wall_slice(cub3d, i, ray);
// 		start.x = cub3d->player.pos.x - cub3d->player.size / 2;
// 		start.y = cub3d->player.pos.y - cub3d->player.size / 2;
// 		draw_line(cub3d->ray_caster.img, start, ray.hit_pos, 1, 0xFF0000FF);
// 		// render_wall_slice(cub3d, i, ray, ray_angle);
// 		i++;
// 	}
// }

// t_ray cast_single_ray(t_cub3d *cub3d, double ray_angle)
// {
// 	t_ray hor_ray;
// 	t_ray ver_ray;
	
// 	hor_ray = cast_horizontal_ray(cub3d, ray_angle);
// 	ver_ray = cast_vertical_ray(cub3d, ray_angle);
// 	if (ver_ray.distance < hor_ray.distance)
// 		return (ver_ray);
// 	return (hor_ray);
// }

// t_ray cast_horizontal_ray(t_cub3d *cub3d, double ray_angle)
// {
// 	t_ray ray;
// 	ray.is_vertical = 0;

// 	double ray_dir_y = sin(ray_angle);
// 	int facing_up = ray_dir_y < 0;

// 	// Erste horizontale Gitterlinie berechnen
// 	double y_intercept = floor(cub3d->player.pos.y / cub3d->map.tile_size) * cub3d->map.tile_size;
// 	y_intercept += facing_up ? -0.0001 : cub3d->map.tile_size;

// 	double x_intercept = cub3d->player.pos.x + (y_intercept - cub3d->player.pos.y) / tan(ray_angle);

// 	// Schrittgrößen
// 	double y_step = facing_up ? -cub3d->map.tile_size : cub3d->map.tile_size;
// 	double x_step = y_step / tan(ray_angle);

// 	double next_x = x_intercept;
// 	double next_y = y_intercept;

// 	// Gitter durchlaufen
// 	while (next_x >= 0 && next_x < cub3d->map.width * cub3d->map.tile_size &&
// 			next_y >= 0 && next_y < cub3d->map.height * cub3d->map.tile_size)
// 	{
// 		int map_x = (int)(next_x / cub3d->map.tile_size);
// 		int map_y = (int)(next_y / cub3d->map.tile_size);

// 		if (map_x >= 0 && map_y >= 0 &&
// 			cub3d->map.grid[map_y][map_x] == '1')
// 		{
// 			ray.hit_pos.x = next_x;
// 			ray.hit_pos.y = next_y;
// 			ray.distance = hypot(next_x - cub3d->player.pos.x, next_y - cub3d->player.pos.y);
// 			return ray;
// 		}

// 		next_x += x_step;
// 		next_y += y_step;
// 	}

// 	// Kein Treffer gefunden
// 	ray.distance = 1e30;
// 	return ray;
// }

// t_ray cast_vertical_ray(t_cub3d *cub3d, double ray_angle)
// {
// 	t_ray ray;
// 	ray.is_vertical = 1;

// 	int facing_left = cos(ray_angle) < 0;

// 	double x_intercept = floor(cub3d->player.pos.x / cub3d->map.tile_size) * cub3d->map.tile_size;
// 	x_intercept += facing_left ? -0.0001 : cub3d->map.tile_size;

// 	double y_intercept = cub3d->player.pos.y + (x_intercept - cub3d->player.pos.x) * tan(ray_angle);

// 	double x_step = facing_left ? -cub3d->map.tile_size : cub3d->map.tile_size;
// 	double y_step = x_step * tan(ray_angle);

// 	double next_x = x_intercept;
// 	double next_y = y_intercept;

// 	while (next_x >= 0 && next_x < cub3d->map.width * cub3d->map.tile_size &&
// 		   next_y >= 0 && next_y < cub3d->map.height * cub3d->map.tile_size)
// 	{
// 		int map_x = (int)(next_x / cub3d->map.tile_size);
// 		int map_y = (int)(next_y / cub3d->map.tile_size);

// 		if (map_x >= 0 && map_y >= 0 &&
// 			cub3d->map.grid[map_y][map_x] == '1')
// 		{
// 			ray.hit_pos.x = next_x;
// 			ray.hit_pos.y = next_y;
// 			ray.distance = hypot(next_x - cub3d->player.pos.x, next_y - cub3d->player.pos.y); //?????
// 			return ray;
// 		}

// 		next_x += x_step;
// 		next_y += y_step;
// 	}

// 	ray.distance = 1e30;
// 	return ray;
// }
