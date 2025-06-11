
#include "cub3d.h"

void clear_image(mlx_image_t *img)
{
	int	y;
	int	x;

	y = 0;
	while (y < (int)img->height)
	{
		x = 0;
		while (x < (int)img->width)
		{
			mlx_put_pixel(img, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

void	draw_img_outline(mlx_image_t *img, int line_width, uint32_t color)
{
	t_point	start;
	t_point	end;

	// Top edge
	start = (t_point){line_width, line_width};
	end = (t_point){img->width - line_width, line_width};
	draw_line(img, start, end, line_width, color);

	// Left edge
	start = (t_point){line_width, line_width};
	end = (t_point){line_width, img->height - line_width};
	draw_line(img, start, end, line_width, color);

	// Right edge
	start = (t_point){img->width - line_width, line_width};
	end = (t_point){img->width - line_width, img->height - line_width};
	draw_line(img, start, end, line_width, color);

	// Bottom edge
	start = (t_point){line_width, img->height - line_width};
	end = (t_point){img->width - line_width, img->height - line_width};
	draw_line(img, start, end, line_width, color);
}


void	draw_background(mlx_image_t *img, uint32_t color)
{
	int	y;
	int	x;

	y = 0;
	while (y < (int)img->height)
	{
		x = 0;
		while (x < (int)img->width)
		{
			if (is_inside_image(img, x, y))
				mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

