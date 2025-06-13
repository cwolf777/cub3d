
#include "cub3d.h"

uint32_t convert_t_rgb_to_rgb_code(t_rgb color)
{
	uint32_t r;
	uint32_t b;
	uint32_t g;
	uint32_t a;

	r = (uint32_t)(color.red & 0xFF) << 24;
	g = (uint32_t)(color.green & 0xFF) << 16;
	b = (uint32_t)(color.blue & 0xFF) << 8;
	a = 0xFF;
	return (r | g | b | a);
}

t_point convert_world_coord_to_minimap_coord(t_cub3d cub3d, double world_x, double world_y)
{
	t_point	point;
	double	offset_x;
	double	offset_y;

	offset_x = cub3d.player.pixel_pos.x - (cub3d.map.width / 2);
	offset_y = cub3d.player.pixel_pos.y - (cub3d.map.height / 2);
	point.x = world_x - offset_x;
	point.y = world_y - offset_y;
	return (point);
}

uint32_t	convert_abgr_to_rgba(uint32_t abgr)
{
	uint8_t	a;
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;

	r = abgr & 0xFF;
	g = (abgr >> 8) & 0xFF;
	b = (abgr >> 16) & 0xFF;
	a = (abgr >> 24) & 0xFF;

	return ((r << 24) | (g << 16) | (b << 8) | a);
}

double	convert_degree_to_rad(int degree)
{
	return (degree * M_PI / 180);
}