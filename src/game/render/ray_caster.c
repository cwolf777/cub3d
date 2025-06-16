
#include "cub3d.h"

t_ray	cast_single_ray(t_cub3d cub3d, double ray_angle)
{
	t_ray	hor_ray;
	t_ray	ver_ray;

	hor_ray = cast_horizontal_ray(cub3d, ray_angle);
	ver_ray = cast_vertical_ray(cub3d, ray_angle);
	if (ver_ray.distance < hor_ray.distance)
		return (ver_ray);
	return (hor_ray);
}

void	ray_caster(t_cub3d cub3d)
{
	int		i;
	t_ray	ray;
	double	start_angle;
	double	ray_angle;

	start_angle = cub3d.player.angle - (cub3d.player.fov / 2.0);
	i = 0;
	while (i < cub3d.ray_caster.num_rays)
	{
		ray_angle = start_angle + i * cub3d.ray_caster.angle_step;
		ray = cast_single_ray(cub3d, ray_angle);
		render_wall_slice(cub3d, i, ray, ray_angle);
		i++;
	}
}
