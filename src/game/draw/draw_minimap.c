
#include "cub3d.h"

void	fill_tile(t_map map, int start_x, int start_y, uint32_t color)
{
	int	pixel_x;
	int	pixel_y;
	int	x;
	int	y;
	
	y = 0;
	while (y < TILE_SIZE - 1)
	{
		x = 0;
		while (x < TILE_SIZE - 1)
		{
			pixel_x = x + start_x;
			pixel_y = y + start_y;
			if (is_inside_image(map.img, pixel_x, pixel_y))
				mlx_put_pixel(map.img, pixel_x, pixel_y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_cub3d cub3d)
{
	int			x;
	int			y;
	int		off_set_x;
	int		off_set_y;

	clear_image(cub3d.map.img);
	draw_background(cub3d.map.img, BLACK_COLOR);
	off_set_x = (int)cub3d.player.pixel_pos.x - (MINIMAP_WIDTH / 2);
	off_set_y = (int)cub3d.player.pixel_pos.y - (MINIMAP_HEIGHT / 2);
	y = 0;
	while(y < cub3d.map.grid_height)
	{
		x = 0;
		while (x < cub3d.map.grid_width)
		{
			if (cub3d.map.grid[y][x] == '1')
				fill_tile(cub3d.map, x * TILE_SIZE - off_set_x, y * TILE_SIZE - off_set_y, GREY_COLOR);
			else
				fill_tile(cub3d.map, x * TILE_SIZE - off_set_x, y * TILE_SIZE - off_set_y, WHITE_COLOR);
			x++;
		}
		y++;
	}
}

void	draw_ray(t_cub3d cub3d, t_ray ray)
{
	t_point	ray_end_pos;
	t_point	ray_start_pos;

	ray_start_pos = (t_point){MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2};
	ray_end_pos = convert_world_coord_to_minimap_coord(cub3d, ray.hit_pos.x, ray.hit_pos.y);
	draw_line(cub3d.ray_caster.img, ray_start_pos, ray_end_pos, YELLOW_COLOR);
}