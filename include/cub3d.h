
#ifndef CUB3D_H
# define CUB3D_H

#define MINIMAP_WIDTH 320
#define MINIMAP_HEIGHT 320
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define MINI_TILE_SIZE 16
#define MINI_PLAYER_SIZE 6
#define PLAYER_COLOR 0xFFAAAAAA
#define DIR_LINE_COLOR 0x0000FF
#define PI 3.1415926535


# include "MLX42.h"
# include "libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# define SEEN_FLAGS_LENGTH 6

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
	int			width;
	int			height;
	char		**grid;
}				t_map;

typedef struct s_player
{
	t_point	pos;
	double	angle;
	char	orientation;
}				t_player;

typedef struct s_ray_hit
{
	double distance; //distanz zu Kollision
	t_point	hit;
	int is_vertical; //1 vertikale, 0 horizontale Wand
}	t_ray_hit;

typedef struct s_cub3d
{
	mlx_t		*mlx;
	t_map		map;
	t_player	player;
	t_graphics	graphics;
	mlx_image_t	*image_buffer;
	mlx_image_t	*player_img;
	mlx_image_t	*map_img; 
	mlx_image_t *ray_img;
	mlx_image_t *view_img;
}				t_cub3d;

//init
void	init_cub3d(t_cub3d *cub3d, char *path);
void	init_img(t_img *img, mlx_t *mlx, char *path);

//parse
void	parse_cub3d(t_cub3d *cub3d, char *path);
void	parse_player(t_cub3d *cub3d);
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
void	render_bg(t_cub3d *cub3d, uint32_t color);
void draw_line(mlx_image_t *image, t_point start, t_point end, int width, uint32_t color);
// void player_controls(mlx_key_data_t keycode, void *param);
void player_controls(void *param);
void	draw_map(t_cub3d *cub3d);
void cast_rays(t_cub3d *cub3d);
t_ray_hit cast_single_ray(t_cub3d *cub3d, double ray_angle);
t_ray_hit cast_horizontal_ray(t_cub3d *cub3d, double ray_angle);
t_ray_hit cast_vertical_ray(t_cub3d *cub3d, double ray_angle);

//render
void	render_map(t_cub3d *cub3d);

//3d
void render_wall_slice(t_cub3d *cub3d, int col, t_ray_hit hit, double ray_angle);

#endif