
#include "cub3d.h"

static void	update_line_values(int *x, int *y, int *err, t_line_helper *h)
{
	int	e2;

	e2 = 2 * (*err);
	if (e2 > -h->dy)
	{
		*err -= h->dy;
		*x += h->sx;
	}
	if (e2 < h->dx)
	{
		*err += h->dx;
		*y += h->sy;
	}
}

void	draw_line(mlx_image_t *img, t_point start, t_point end, uint32_t color)
{
	t_point_int		p;
	int				err;
	t_line_helper	h;

	p = (t_point_int){(int)start.x, (int)start.y};
	h.dx = abs((int)end.x - p.x);
	h.dy = abs((int)end.y - p.y);
	if (p.x < (int)end.x)
		h.sx = 1;
	else
		h.sx = -1;
	if (p.y < (int)end.y)
		h.sy = 1;
	else
		h.sy = -1;
	err = h.dx - h.dy;
	while (1)
	{
		if (is_inside_image(img, p.x, p.y))
			mlx_put_pixel(img, p.x, p.y, color);
		if (p.x == (int)end.x && p.y == (int)end.y)
			break ;
		update_line_values(&p.x, &p.y, &err, &h);
	}
}
