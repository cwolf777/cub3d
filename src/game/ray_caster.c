
#include "cub3d.h"

int	calc_y_step(double ray_angle)
{
	if (sin(ray_angle) < 0)
		return (-TILE_SIZE);
	return (TILE_SIZE);
}
int	calc_x_step(double ray_angle)
{
	if (cos(ray_angle) < 0)
		return (-TILE_SIZE);
	return (TILE_SIZE);
}

void calculate_delta_dist(t_point *ray_dir, t_point *delta_dist)
{
	delta_dist->x = (ray_dir->x== 0) ? 1e30 : fabs(TILE_SIZE / ray_dir->x);
	delta_dist->y = (ray_dir->y == 0) ? 1e30 : fabs(TILE_SIZE / ray_dir->y);
}

double calculate_hit_distance(bool is_vertical, t_point side_dist, t_point delta_dist)
{
	if (is_vertical)
		return (side_dist.x - delta_dist.x);
	else
		return (side_dist.y - delta_dist.y);
}

bool perform_dda(t_cub3d cub3d, t_point ray_dir, t_point delta_dist)
{
	bool		is_vertical;
	t_point_int	grid_pos;
	t_point	side_dist;
	t_point_int	step;
	

	grid_pos = (t_point_int){cub3d.player.grid_pos.x, cub3d.player.grid_pos.y};
	is_vertical = false;
	step = calculate_step(cub3d, ray_dir);
	side_dist = calculate_side_dist(cub3d, ray_dir);
	while (1)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			grid_pos.x += step.x;
			is_vertical = true;
		}
		else
		{
			side_dist.y += delta_dist.y;
			grid_pos.y += step.y;
			is_vertical = false;
		}

		if (grid_pos.y >= 0 && grid_pos.y < cub3d.map.grid_height &&
			grid_pos.y >= 0 && grid_pos.y < cub3d.map.grid_width &&
			cub3d.map.grid[grid_pos.y][grid_pos.y] == '1')
		{
			return (is_vertical);
		}
	}
}
t_point calculate_side_dist(t_cub3d cub3d, t_point ray_dir)
{
	t_point		player_pos;
	t_point_int	grid_pos;
	t_point		side_dist;

	player_pos = (t_point){cub3d.player.pos.x, cub3d.player.pos.y};
	grid_pos = (t_point_int){cub3d.player.grid_pos.x, cub3d.player.grid_pos.y};

	if (ray_dir.x < 0)
		side_dist.x = (player_pos.x - grid_pos.x * TILE_SIZE) / fabs(ray_dir.x);
	else
		side_dist.x = ((grid_pos.x + 1) * TILE_SIZE - player_pos.x) / fabs(ray_dir.x);

	if (ray_dir.y < 0)
		side_dist.y = (player_pos.y - grid_pos.y * TILE_SIZE) / fabs(ray_dir.y);
	else
		side_dist.y = ((grid_pos.y + 1) * TILE_SIZE - player_pos.y) / fabs(ray_dir.y);
	return (side_dist);
}
t_point_int calculate_step(t_cub3d cub3d, t_point ray_dir)
{
	t_point_int	step;

	if (ray_dir.x < 0)
		step.x = -1;
	else
		step.x = 1;

	if (ray_dir.y < 0)
		step.y = -1;
	else
		step.y = 1;
	return (step);
}


t_ray cast_ray(t_cub3d cub3d, double ray_angle)
{
	t_ray ray;
	bool	is_vertical;
	t_point	ray_dir;
	t_point	delta_dist;
	t_point_int	step;

	ray_dir = (t_point){cos(ray_angle), sin(ray_angle)};

	// Schrittweiten berechnen
	calculate_delta_dist(&ray_dir, &delta_dist);
	// Startdistanz und Schritte berechnen
	calculate_side_dist(cub3d, ray_dir, &step, );
	// DDA durchführen
	is_vertical = perform_dda(cub3d, &data);

	// Trefferentfernung berechnen
	ray.distance = calculate_hit_distance(data);

	ray.distance = hit_distance;
	ray.hit_pos.x = cub3d.player.pos.x + ray_dir_x * hit_distance;
	ray.hit_pos.y = cub3d.player.pos.y + ray_dir_y * hit_distance;
	ray.is_vertical = data.is_vertical;

	return ray;
}


void ray_caster(t_cub3d cub3d)
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
		ray = cast_ray(cub3d, ray_angle);
		if (cub3d.ray_caster.is_visible)
			draw_ray(cub3d, ray);
		render_wall_slice(cub3d, i, ray, ray_angle);
		i++;
	}
}

