
#include "cub3d.h"

static t_ray	find_wall_hit(t_cub3d cub3d, t_ray ray, t_ray_data data)
{
	double	next_x;
	double	next_y;
	int		map_x;
	int		map_y;

	next_x = data.x_intercept;
	next_y = data.y_intercept;
	while (next_x >= 0 && next_x < cub3d.map.grid_width * TILE_SIZE
		&& next_y >= 0 && next_y < cub3d.map.grid_height * TILE_SIZE)
	{
		map_x = (int)(next_x / TILE_SIZE);
		map_y = (int)(next_y / TILE_SIZE);
		if (cub3d.map.grid[map_y][map_x] == '1')
		{
			ray.hit_pos.x = next_x;
			ray.hit_pos.y = next_y;
			ray.distance = hypot(next_x - cub3d.player.pixel_pos.x,
					next_y - cub3d.player.pixel_pos.y);
			return (ray);
		}
		next_x += data.x_step;
		next_y += data.y_step;
	}
	ray.distance = 1e30;
	return (ray);
}

t_ray	cast_ray_generic(t_cub3d cub3d, double angle, int is_vertical)
{
	t_ray		ray;
	t_ray_data	data;

	ray.is_vertical = is_vertical;
	if (is_vertical)
		data = init_vertical_ray(cub3d, angle);
	else
		data = init_horizontal_ray(cub3d, angle);
	return (find_wall_hit(cub3d, ray, data));
}
