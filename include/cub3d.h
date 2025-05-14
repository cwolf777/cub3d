
#ifndef CUB3D_H
# define CUB3D_H

#define MAP_WIDTH 1280
#define MAP_HEIGHT 720
#define TILE_SIZE 64
#define PLAYER_SIZE 16
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
// # define NO "NO"
// # define WE "WE"
// # define EA "EA"
// # define SO "SO"

typedef struct s_ray_hit
{
	double distance; //distanz zu Kollision
	int hit_x; //Koord der Kollision
	int hit_y;
	int is_vertical; //1 vertikale, 0 horizontale Wand
}	t_ray_hit;

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
	char	orientation;
}				t_player;

typedef struct s_cub3d
{
	mlx_t		*mlx;
	t_map		map;
	t_player	player;
	t_graphics	graphics;
	mlx_image_t	*image_buffer; //neu
	mlx_image_t	*player_img; //neu
	t_point		player_pos;
	double		player_angle;
	mlx_image_t *ray_img;
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
void	cast_ray(t_cub3d *cub3d);
void cast_rays(t_cub3d *cub3d);

#endif