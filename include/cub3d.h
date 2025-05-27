
#ifndef CUB3D_H
# define CUB3D_H

//COLORS
#define WHITE 0xFFFFFFFF
#define GREEN 0xFFFF3333
#define PLAYER_COLOR 0xFFAAAAAA

#define MINIMAP_WIDTH 260
#define MINIMAP_HEIGHT 152
#define MINIMAP_VIEW_SIZE 3
#define TILE_SIZE 32
#define PLAYER_SIZE 10
#define PLAYER_SPEED 2
#define PLAYER_ROT_SPEED 
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define DIR_LINE_COLOR 0x0000FF
// #define PI 3.1415926535


# include "MLX42.h"
# include "libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# define GRAPHICS_LENGTH 6

typedef enum e_graphic_config
{
	NO = 0,
	WE,
	EA,
	SO,
	F,
	C
} t_graphic_config;


typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}				t_rgb;

typedef struct s_img
{
	int			type;
	mlx_image_t	*img;
	char		*path;
}				t_img;

typedef struct s_graphics
{
	t_img		north;
	t_img		west;
	t_img		east;
	t_img		south;
	t_rgb		floor;
	t_rgb		ceiling;
}				t_graphics;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_map
{
	int			grid_width;
	int			grid_height;
	// int			pixel_width;
	// int			pixel_height;
	char		**grid;
	t_point		player_index;
	char		player_orientation;
	// int			tile_size;
	mlx_image_t	*img;
}				t_map;

typedef struct s_player
{
	t_point		pixel_pos;
	t_point		grid_pos;
	double		angle;
	int			speed;
	double		rot_speed;
	int			size;
	double		fov;
	mlx_image_t	*img;
}				t_player;

typedef struct s_ray
{
	bool		is_vertical;
	double		distance; //distanz zu Kollision
	t_point		hit_pos;
}	t_ray;

typedef struct s_ray_caster
{

	int			num_rays;
	double		angle_step;
	double		start_angle;
	mlx_image_t	*img;
}	t_ray_caster;

typedef struct s_cub3d
{
	mlx_t			*mlx;
	t_map			map;
	t_player		player;
	t_graphics		graphics;
	t_ray_caster	ray_caster;
	mlx_image_t		*view_img;
}				t_cub3d;

//init
void	init_cub3d(t_cub3d *cub3d, char *path);
void	init_img(t_img *img, mlx_t *mlx, char *path);

//parse
void	parse_cub3d(t_cub3d *cub3d, char *path);
void	parse_graphics(t_cub3d *cub3d, int fd);
void	parse_map(t_map *map, int fd);
void	load_rgb(t_cub3d *cub3d, int *seen_flags, char *str);
void	load_texture(t_cub3d *cub3d, int *seen_flags, char *str);

//validation
void	validate_cub3d(t_cub3d cub3d);
bool	validate_file_extension(char *path, char *extension);
void	validate_grid(t_cub3d cub3d);
void	validate_rgb(t_rgb rgb);
void	validate_player(t_map map);
void	flood_fill(char **grid, int x, int y);

//error
void	handle_error(char *error_msg);

//utils
bool	is_white_space(char c);
char	**copy_grid(t_map map);
void	free_grid(char **map);
void	skip_whitespace(char **str);
bool	is_valid_digit_string(char *str);
char	*clean_str(char *str);
char	**ft_split2(char const *s, char *delimiters);
double	degree_to_rad(int degree);

//print
void	print_grid(char **grid);
void	print_cub3d_info(t_cub3d *cub);

//minimap
void	render_player(t_cub3d *cub3d);
// void	render_bg(t_cub3d *cub3d, uint32_t color);
void cast_rays(t_cub3d *cub3d);
t_ray cast_single_ray(t_cub3d *cub3d, double ray_angle);
t_ray cast_horizontal_ray(t_cub3d *cub3d, double ray_angle);
t_ray cast_vertical_ray(t_cub3d *cub3d, double ray_angle);

//render
void	render_map(t_cub3d *cub3d);

//draw
void	draw_line(mlx_image_t *image, t_point start, t_point end, int width, uint32_t color);
void	draw_filled_circle(mlx_image_t *img, t_point center, int radius, uint32_t color);
void	draw_player(t_cub3d *cub3d);
void	fill_tile(t_map map, int x, int y, uint32_t color);
void	draw_minimap(t_cub3d cub3d);
void	draw_img_outline(mlx_image_t *img, int line_width, uint32_t color);
void	clear_image(mlx_image_t *img);
void	draw_map_centered(t_map map);

//player_controls
void	player_movement(t_cub3d *cub3d);

//game
void	game_loop(void *param);
void	handle_keypress(mlx_key_data_t keydata, void *param);
void	handle_close(void *param);

//3d
void		render_wall_slice(t_cub3d *cub3d, int col, t_ray ray, double ray_angle);
uint32_t	rgb_to_color(t_rgb color);
void		fill_background(t_cub3d *cub3d);

#endif