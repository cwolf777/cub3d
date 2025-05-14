#include "cub3d.h"

void	draw_background(t_cub3d *cub3d, uint32_t color)
{
	mlx_image_t *background = mlx_new_image(cub3d->mlx, 1280, 720);
	if (!background)
		handle_error("Failed to create background");

	for (int y = 0; y < 720; y++)
	{
		for (int x = 0; x < 1280; x++)
		{
			mlx_put_pixel(background, x, y, color);
		}
	}

	if (mlx_image_to_window(cub3d->mlx, background, 0, 0) < 0)
		handle_error("Failed to draw background");
}

void	render_player(t_cub3d *cub3d)
{
	int32_t	size = PLAYER_SIZE;
	uint32_t color = 0xFFAAAAAA;
	uint32_t line_color = 0x0000FF;  // Rot für Blickrichtung

	if (cub3d->player_img)
	{
		mlx_delete_image(cub3d->mlx, cub3d->player_img);
		cub3d->player_img = NULL;
	}
	cub3d->player_img = mlx_new_image(cub3d->mlx, size, size);
	if (!cub3d->player_img)
		handle_error("Player image creation failed");

	for (int y = 0; y < size; y++)
		for (int x = 0; x < size; x++)
			mlx_put_pixel(cub3d->player_img, x, y, color);
	
	// Mittelpunkt des Spielers
	int center_x = size / 2;
	int center_y = size / 2;

	// Richtung berechnen
	double angle = cub3d->player_angle;
	int line_len = 100;

	// int end_x = center_x + cos(angle) * line_len;
	// int end_y = center_y + sin(angle) * line_len;

	// Linie von Mitte zur Blickrichtung
	// Simple Bresenham oder hier einfach direkte Linie:
	for (int i = 0; i < line_len; i++)
	{
		int px = center_x + cos(angle) * i;
		int py = center_y + sin(angle) * i;
		if (px >= 0 && px < size && py >= 0 && py < size)
			mlx_put_pixel(cub3d->player_img, px, py, line_color);
	}

	if (mlx_image_to_window(cub3d->mlx, cub3d->player_img, cub3d->player_pos.x, cub3d->player_pos.y) < 0)
		handle_error("Failed to draw player");
}

void player_controls( void *param)
{
	t_cub3d *cub3d = (t_cub3d *)param;
	// (void)keycode;
	int speed = 5;
	double rot_speed = 0.100530964912;
	
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
	{
		cub3d->player_pos.x += cos(cub3d->player_angle) * speed;
		cub3d->player_pos.y += sin(cub3d->player_angle) * speed;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
	{
		cub3d->player_pos.x -= cos(cub3d->player_angle) * speed;
		cub3d->player_pos.y -= sin(cub3d->player_angle) * speed;		
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		cub3d->player_angle -= rot_speed;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		cub3d->player_angle += rot_speed;

	render_player(cub3d);
	// cast_ray(cub3d);
	cast_rays(cub3d);
}

void	draw_map(t_cub3d *cub3d)
{
	uint32_t fill_color;
	uint32_t outline_color = 0xFF000000;

	for (int y = 0; y < cub3d->map.height; y++)
	{
		for (int x = 0; x < cub3d->map.width; x++)
		{
			char tile = cub3d->map.grid[y][x];

			if (tile == '1')
				fill_color = 0xFFFF3333;
			else if (tile == '0')
				fill_color = 0xFFFFFFFF;
			else if (tile == 'N' || tile == 'S' || tile == 'W' || tile == 'E')
				fill_color = 0xFFFFFFFF; // Spielerposi auch weiss

			mlx_image_t *tile_img = mlx_new_image(cub3d->mlx, TILE_SIZE, TILE_SIZE);
			if (!tile_img)
				handle_error("Tile image creation failed");

			for (int ty = 0; ty < TILE_SIZE; ty++)
			{
				for (int tx = 0; tx < TILE_SIZE; tx++)
				{
					// Zeichne Rahmen (1 Pixel dick)
					if (tx == 0 || ty == 0 || tx == TILE_SIZE - 1 || ty == TILE_SIZE - 1)
						mlx_put_pixel(tile_img, tx, ty, outline_color);
					else
						mlx_put_pixel(tile_img, tx, ty, fill_color);
				}
			}

			if (mlx_image_to_window(cub3d->mlx, tile_img, x * TILE_SIZE, y * TILE_SIZE) < 0)
				handle_error("Failed to draw map tile");
		}
	}
}

void cast_rays(t_cub3d *cub3d)
{
	int num_rays = 60;
	double fov = 60.0 * (M_PI / 180.0); // z. B. 60 Grad
	double angle_step = fov / num_rays;
	double start_angle = cub3d->player_angle - (fov / 2.0);

	for (int i = 0; i < num_rays; i++)
	{
		double ray_angle = start_angle + i * angle_step;
		t_ray_hit hit = cast_single_ray(cub3d, ray_angle);

		// 3D Wandhöhe berechnen & zeichnen
		// render_wall_slice(cub3d, i, hit);

		// Optional: Ray auf Minimap zeichnen
		// render_ray_on_minimap(cub3d, hit.hit_x, hit.hit_y);
	}
}


t_ray_hit cast_single_ray(t_cub3d *cub3d, double ray_angle)
{
	t_ray_hit hor_hit = cast_horizontal_ray(cub3d, ray_angle);
	t_ray_hit ver_hit = cast_vertical_ray(cub3d, ray_angle);

	if (ver_hit.distance < hor_hit.distance)
		return ver_hit;
	else
		return hor_hit;
}

t_ray_hit cast_horizontal_ray(t_cub3d *cub3d, double ray_angle)
{
	t_ray_hit hit;
	hit.is_vertical = 0;

	double ray_dir_y = sin(ray_angle);
	double ray_dir_x = cos(ray_angle);

	// Richtung prüfen: schauen wir nach oben oder unten?
	int facing_up = ray_dir_y < 0;

	// Erste horizontale Gitterlinie berechnen
	double y_intercept = floor(cub3d->player_pos.y / TILE_SIZE) * TILE_SIZE;
	y_intercept += facing_up ? -0.0001 : TILE_SIZE;

	double x_intercept = cub3d->player_pos.x + (y_intercept - cub3d->player_pos.y) / tan(ray_angle);

	// Schrittgrößen
	double y_step = facing_up ? -TILE_SIZE : TILE_SIZE;
	double x_step = y_step / tan(ray_angle);

	double next_x = x_intercept;
	double next_y = y_intercept;

	// Gitter durchlaufen
	while (next_x >= 0 && next_x < cub3d->map.width * TILE_SIZE &&
		   next_y >= 0 && next_y < cub3d->map.height * TILE_SIZE)
	{
		int map_x = (int)(next_x / TILE_SIZE);
		int map_y = (int)(next_y / TILE_SIZE);

		if (map_x >= 0 && map_y >= 0 &&
			cub3d->map.grid[map_y][map_x] == '1')
		{
			hit.hit_x = next_x;
			hit.hit_y = next_y;
			hit.distance = hypot(next_x - cub3d->player_pos.x, next_y - cub3d->player_pos.y);
			return hit;
		}

		next_x += x_step;
		next_y += y_step;
	}

	// Kein Treffer gefunden
	hit.distance = 1e30;
	return hit;
}

t_ray_hit cast_vertical_ray(t_cub3d *cub3d, double ray_angle)
{
	t_ray_hit hit;
	hit.is_vertical = 1;

	double ray_dir_y = sin(ray_angle);
	double ray_dir_x = cos(ray_angle);

	// Nach links oder rechts?
	int facing_left = ray_dir_x < 0;

	double x_intercept = floor(cub3d->player_pos.x / TILE_SIZE) * TILE_SIZE;
	x_intercept += facing_left ? -0.0001 : TILE_SIZE;

	double y_intercept = cub3d->player_pos.y + (x_intercept - cub3d->player_pos.x) * tan(ray_angle);

	double x_step = facing_left ? -TILE_SIZE : TILE_SIZE;
	double y_step = x_step * tan(ray_angle);

	double next_x = x_intercept;
	double next_y = y_intercept;

	while (next_x >= 0 && next_x < cub3d->map.width * TILE_SIZE &&
		   next_y >= 0 && next_y < cub3d->map.height * TILE_SIZE)
	{
		int map_x = (int)(next_x / TILE_SIZE);
		int map_y = (int)(next_y / TILE_SIZE);

		if (map_x >= 0 && map_y >= 0 &&
			cub3d->map.grid[map_y][map_x] == '1')
		{
			hit.hit_x = next_x;
			hit.hit_y = next_y;
			hit.distance = hypot(next_x - cub3d->player_pos.x, next_y - cub3d->player_pos.y);
			return hit;
		}

		next_x += x_step;
		next_y += y_step;
	}

	hit.distance = 1e30;
	return hit;
}
