
#include "cub3d.h"

void	clear_image(mlx_image_t *img)
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
