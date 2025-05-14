
#include "cub3d.h"

void draw_line(mlx_image_t *image, t_point start, t_point end, int width, uint32_t color)
{
	int dx = abs(end.x - start.x);
	int dy = -abs(end.y - start.y);
	int sx = start.x < end.x ? 1 : -1;
	int sy = start.y < end.y ? 1 : -1;
	int err = dx + dy;
	int e2;

	int x = start.x;
	int y = start.y;

	while (1)
	{
		// Zeichne Pixel mit Breite (kleines Quadrat um den Punkt)
		for (int i = -width / 2; i <= width / 2; i++)
		{
			for (int j = -width / 2; j <= width / 2; j++)
			{
				int px = x + i;
				int py = y + j;

				// Nur zeichnen, wenn im Bildbereich
				if (px >= 0 && py >= 0 && px < (int)image->width && py < (int)image->height)
					mlx_put_pixel(image, px, py, color);
			}
		}

		// Abbruchbedingung
		if (x == end.x && y == end.y)
			break;

		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y += sy;
		}
	}
}