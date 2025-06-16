
#include "cub3d.h"

mlx_image_t	*get_wall_texture(t_cub3d cub3d, t_ray ray, double ray_angle)
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

void	render_wall_slice(t_cub3d cub3d, int draw_x,
	t_ray ray, double ray_angle)
{
	t_wall_slice	slice;
	double			corrected_dist;
	double			wall_height;
	double			offset;

	corrected_dist = ray.distance
		* cos(ray_angle - cub3d.player.angle);
	wall_height = (TILE_SIZE / corrected_dist)
		* cub3d.ray_caster.dist_proj_plane;
	slice.wall_top = (int)((cub3d.window_height / 2) - (wall_height / 2));
	slice.wall_bottom = (int)((cub3d.window_height / 2) + (wall_height / 2));
	slice.y = slice.wall_top;
	slice.wall_img = get_wall_texture(cub3d, ray, ray_angle);
	if (ray.is_vertical)
		offset = (int)ray.hit_pos.y % TILE_SIZE;
	else
		offset = (int)ray.hit_pos.x % TILE_SIZE;
	slice.offset_x = (int)(offset * (slice.wall_img->width / TILE_SIZE));
	draw_wall_slice(cub3d, slice, draw_x);
}
