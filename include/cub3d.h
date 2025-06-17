
#ifndef CUB3D_H
# define CUB3D_H

//COLORS
# define WHITE_COLOR 0xFFFFFFFF
# define GREY_COLOR 0x555555FF
# define BLACK_COLOR 0x000000FF
# define PLAYER_COLOR 0x1E90FFFF
# define YELLOW_COLOR 0xFFFF00FF

//MAP
# define MINIMAP_WIDTH 260
# define MINIMAP_HEIGHT 152
# define MINIMAP_VIEW_SIZE 3
# define TILE_SIZE 32

//PLAYER
# define PLAYER_SIZE 10
# define PLAYER_SPEED 150.0
# define PLAYER_ROT_SPEED (M_PI / 2)
# define DIR_LINE_COLOR 0x0000FF

//SETTINGS
# define MIN_WINDOW_WIDTH 640
# define MIN_WINDOW_HEIGHT 480
# define MAX_WINDOW_WIDTH -1
# define MAX_WINDOW_HEIGHT -1
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define GRAPHICS_LENGTH 6


#include "MLX42.h"
#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "utils.h"
#include "types.h"

//init
void	init_cub3d(t_cub3d *cub3d, char *path);
void	init_img(t_cub3d *cub3d, t_img *img, mlx_t *mlx, char *path);
void	init_ray_caster(t_cub3d *cub3d);
void	init_map(t_cub3d *cub3d);

//parse
void	parse_cub3d(t_cub3d *cub3d, char *path);
void	parse_graphics(t_cub3d *cub3d, int fd);
void	parse_map(t_cub3d *cub3d, t_map *map, int fd);
void	load_rgb(t_cub3d *cub3d, int *seen_flags, char *str);
void	load_texture(t_cub3d *cub3d, int *seen_flags, char *str);

//validation
void	validate_cub3d(t_cub3d cub3d);
bool	validate_file_extension(char *path, char *extension);
void	validate_grid(t_cub3d *cub3d);
bool	validate_rgb(t_rgb rgb);
void	validate_player(t_cub3d *cub3d, t_map map);
void	flood_fill(t_cub3d *cub3d, char **grid, int x, int y);


//minimap
void ray_caster(t_cub3d cub3d);
t_ray cast_single_ray(t_cub3d cub3d, double ray_angle);
t_ray cast_horizontal_ray(t_cub3d cub3d, double ray_angle);
t_ray cast_vertical_ray(t_cub3d cub3d, double ray_angle);

//render
void	render_3d(t_cub3d cub3d);

//draw
void	draw_line(mlx_image_t *image, t_point start, t_point end, uint32_t color);
void	draw_filled_circle(mlx_image_t *img, t_point center, int radius, uint32_t color);
void	draw_player(t_cub3d cub3d);
void	fill_tile(t_map map, int x, int y, uint32_t color);
void	draw_minimap(t_cub3d cub3d);
void	draw_ray(t_cub3d cub3d, t_ray ray);
void	clear_image(mlx_image_t *img);
void	draw_background(mlx_image_t *img, uint32_t color);
void	draw_ceiling(t_cub3d cub3d);
void	draw_floor(t_cub3d cub3d);
void	draw_wall_slice(t_cub3d cub3d, mlx_image_t *wall_img, int x, int y, int offset_x, int wall_bottom, int wall_top);

//player_controls
bool	check_collision(t_map map, double px, double py);
void	player_movement(t_cub3d *cub3d);
void	rotate_left(t_cub3d *cub3d, double delta_time);
void	rotate_right(t_cub3d *cub3d, double delta_time);
void	move_forward(t_cub3d *cub3d, double *move_x, double *move_y, double delta_time);
void	move_backward(t_cub3d *cub3d, double *move_x, double *move_y, double delta_time);
void	move_left(t_cub3d *cub3d, double *move_x, double *move_y, double delta_time);
void	move_right(t_cub3d *cub3d, double *move_x, double *move_y, double delta_time);

//game
void	game_loop(void *param);
void	handle_keypress(mlx_key_data_t keydata, void *param);
void	handle_close(void *param);
void	handle_resize(int width, int height, void *param);

//3d
void		render_wall_slice(t_cub3d cub3d, int col, t_ray ray, double ray_angle);

#endif