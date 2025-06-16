
#ifndef UTILS_H
# define UTILS_H

#include "types.h"

char		**copy_grid(t_cub3d *cub3d, t_map map);

//str_utils
bool		is_white_space(char c);
void		skip_whitespace(char **str);
bool		is_valid_digit_string(char *str);
char		*clean_str(char *str);
bool		no_double_newline(char *str);

//ft_split2
char		**ft_split2(char const *s, char *delimiters);

//convert
double		convert_degree_to_rad(int degree);
uint32_t	convert_abgr_to_rgba(uint32_t abgr);
uint32_t	convert_t_rgb_to_rgb_code(t_rgb color);
t_point		convert_world_coord_to_minimap_coord(t_cub3d cub3d, double world_x, double world_y);

//free
void		free_cub3d(t_cub3d *cub3d);
void		free_grid(char **map);

//error
void		handle_error(t_cub3d *cub3d, char *error_msg);

//print
void		print_grid(char **grid);
void		print_cub3d_info(t_cub3d *cub);

//mlx
void		set_layer_order(t_cub3d *cub3d);
bool 		is_inside_image(mlx_image_t *img, int x, int y);
void		create_view(t_cub3d *cub3d);
void		create_minimap(t_cub3d *cub3d);
void		setup_mlx(t_cub3d *cub3d);

#endif