
#ifndef CUB3D_H
# define CUB3D_H

#define TILE_SIZE 64
#define PLAYER_SIZE 16
#define PI 3.1415926535


# include "MLX42.h"
# include "libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>


typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}				t_rgb;

typedef struct s_img
{
	mlx_image_t	*img;
	char		*path;
}				t_img;

typedef struct s_graphics
{
	t_img	north;
	t_img	west;
	t_img	east;
	t_img	south;
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

typedef struct s_cub3d
{
	mlx_t		*mlx;
	t_map		map;
	t_graphics	graphics;
	mlx_image_t	*image_buffer; //neu
	mlx_image_t	*player_img; //neu
	t_point		player_pos;
	double		player_angle;
	mlx_image_t *ray_img;
}				t_cub3d;

//init
void	init_cub3d(t_cub3d *cub3d, char *path);

//map
char	**create_grid(char *path);
void	init_map_size(t_map *map);

//validation
bool	validate_file_extension(char *path, char *extension);
void	validate_grid(char **grid);
bool	validate_rgb(t_rgb rgb);

//error
void	handle_error(char *error_msg);

//utils
void	free_map(char **map);
void	skip_whitespace(char **str);
bool	is_valid_digit_string(char *str);

//print
void	print_grid(char **grid);
void	print_cub3d_info(t_cub3d *cub);

//minimap
void	render_player(t_cub3d *cub3d);
void	draw_background(t_cub3d *cub3d, uint32_t color);
void	player_controls(void *param);
void	draw_map(t_cub3d *cub3d);
void	cast_ray(t_cub3d *cub3d);

#endif