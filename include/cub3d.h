
#ifndef CUB3D_H
# define CUB3D_H


# include "MLX42.h"
# include "libft.h"
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}				t_rgb;

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
	t_rgb		floor;
	t_rgb		ceiling;
}				t_map;

typedef struct s_cub3d
{
	mlx_t		*mlx;
	t_map		map;
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


#endif