

#include "cub3d.h"

void	init_map(t_map *map, char *path)
{

	map->grid = create_grid(path);
	validate_grid(map->grid);
	init_map_size(map);
}

int		extract_color_code(char *str)
{
	int	color_code;
	if (!str)
		handle_error("Failed to init color");
	skip_whitespaces(&str);
	if (!is_valid_digit_string(str))
		handle_error("Failed to init color");
	color_code = ft_atoi(str);
	return (color_code);
}

void	init_rgb(t_rgb *rgb, char *line)
{
	char	**rgb_arr;

	skip_whitespaces(&line);
	rgb_arr = ft_split(line, ',');

}

void	init_colors(t_cub3d *cub3d, char *path)
{
	int	fd;
	char	*curr_line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		handle_error("Failed to open file");
	
	curr_line = get_next_line(fd);
	skip_whitespace(&curr_line);
	if (curr_line[0] == 'F')
		init_rgb(&cub3d->map.floor, curr_line);

}

void	init_cub3d(t_cub3d *cub3d, char *path)
{
	init_map(&cub3d->map, path);
	init_colors(cub3d, path);
	cub3d->mlx = mlx_init(cub3d->map.width * 50, cub3d->map.height * 50, "Cub3d", false);

}