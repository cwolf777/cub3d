
#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
# include "MLX42.h"

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
	double			x;
	double			y;
}				t_point;

typedef struct s_map
{
	int			grid_width;
	int			grid_height;
	char		**grid;
	t_point		player_index;
	char		player_orientation;
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
	double		distance;
	t_point		hit_pos;
}	t_ray;

typedef struct s_ray_caster
{

	int			num_rays;
	double		angle_step;
	double		start_angle;
	double		dist_proj_plane;
	int			wall_top;
	int			wall_bottom;
	mlx_image_t	*img;
}	t_ray_caster;

typedef struct s_cub3d
{
	mlx_t			*mlx;
	int				fd;
	t_map			map;
	t_player		player;
	t_graphics		graphics;
	t_ray_caster	ray_caster;
	mlx_image_t		*view_img;
	int				window_width;
	int				window_height;
}				t_cub3d;

typedef struct s_line_helper
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
}				t_line_helper;

typedef struct s_point_int
{
	int			x;
	int			y;
}				t_point_int;

#endif