
#include "cub3d.h"

void	draw_ceiling(t_cub3d cub3d)
{
	int			y;
	int			x;
	uint32_t	ceiling_color;

	ceiling_color = convert_t_rgb_to_rgb_code(cub3d.graphics.ceiling);
	y = 0;
	while (y < cub3d.window_height / 2)
	{
		x = 0;
		while (x < cub3d.window_width)
		{
			if (is_inside_image(cub3d.view_img, x, y))
				mlx_put_pixel(cub3d.view_img, x, y, ceiling_color);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_cub3d cub3d)
{
	int			y;
	int			x;
	uint32_t	floor;

	floor = convert_t_rgb_to_rgb_code(cub3d.graphics.floor);
	y = cub3d.window_height / 2;
	while (y < cub3d.window_height)
	{
		x = 0;
		while (x < cub3d.window_width)
		{
			if (is_inside_image(cub3d.view_img, x, y))
				mlx_put_pixel(cub3d.view_img, x, y, floor);
			x++;
		}
		y++;
	}
}

void	draw_wall_slice(t_cub3d cub3d, t_wall_slice s, int draw_x)
{
	double		wall_y_ratio;
	uint32_t	wall_color;
	int			tex_y;
	uint32_t	*pixels;

	pixels = (uint32_t *)s.wall_img->pixels;
	while (s.y < s.wall_bottom)
	{
		wall_y_ratio = (double)(s.y - s.wall_top)
			/ (s.wall_bottom - s.wall_top);
		tex_y = wall_y_ratio * s.wall_img->height;
		wall_color = pixels[tex_y * s.wall_img->width + s.offset_x];
		if (is_inside_image(cub3d.view_img, draw_x, s.y))
			mlx_put_pixel(cub3d.view_img, draw_x, s.y,
				convert_abgr_to_rgba(wall_color));
		s.y++;
	}
}
