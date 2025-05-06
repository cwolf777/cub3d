
#ifndef CUB3D_H
# define CUB3D_H


# include "MLX42.h"
# include "libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>

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
}				t_cub3d;

//init
void	init_cub3d(t_cub3d *cub3d, char *path);
void	init_img(t_img *img, mlx_t *mlx, char *path);

//parse
void	parse_player(t_cub3d *cub3d);
void	parse_graphics(t_cub3d *cub3d, int fd);
void	parse_map(t_map *map, int fd);
void	load_rgb(t_cub3d *cub3d, int *seen_flags, char *str);
void	load_texture(t_cub3d *cub3d, int *seen_flags, char *str);

//validation
bool	validate_file_extension(char *path, char *extension);
void	validate_grid(char **grid);
bool	validate_rgb(t_rgb rgb);
bool	validate_player(t_map map);

//error
void	handle_error(char *error_msg);

//utils
char	**copy_grid(t_map map);
void	free_grid(char **map);
void	skip_whitespace(char **str);
bool	is_valid_digit_string(char *str);
char	*clean_str(char *str);
void	flood_fill(char **grid, int x, int y);

//print
void	print_grid(char **grid);
void	print_cub3d_info(t_cub3d *cub);


#endif