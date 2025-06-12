#include "cub3d.h"

mlx_image_t *get_wall_texture(t_cub3d cub3d, t_ray ray, double ray_angle)
{
	if (ray.is_vertical)
	{
		if (cos(ray_angle) < 0)
			return (cub3d.graphics.west.img);
		else
			return (cub3d.graphics.east.img);
	}
	else
	{
		if (sin(ray_angle) < 0)
			return (cub3d.graphics.north.img);
		else
			return (cub3d.graphics.south.img);
	}
}

void render_wall_slice(t_cub3d cub3d, int draw_x, t_ray ray, double ray_angle)
{
	double		corrected_distance;
	mlx_image_t	*wall_texture;
	double			offset_x;

	corrected_distance = ray.distance * cos(ray_angle - cub3d.player.angle);
	// Konstanten für Projektion
	double wall_height = (TILE_SIZE / corrected_distance) * cub3d.ray_caster.dist_proj_plane;
	double wall_top = (cub3d.window_height / 2) - (wall_height / 2);
	double wall_bottom = (cub3d.window_height / 2) + (wall_height / 2);

	wall_texture = get_wall_texture(cub3d, ray, ray_angle);
	if (ray.is_vertical)
		offset_x = (int)ray.hit_pos.y % TILE_SIZE;
	else
		offset_x = (int)ray.hit_pos.x % TILE_SIZE;
	offset_x = offset_x * (wall_texture->width / TILE_SIZE);
	draw_wall_slice(cub3d, wall_texture, draw_x, wall_top, offset_x, wall_bottom, wall_top);
}
