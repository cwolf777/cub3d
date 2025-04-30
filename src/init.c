

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
		handle_error("NULL string in extract_color_code()");
	skip_whitespace(&str);
	if (!is_valid_digit_string(str))
		handle_error("Not valid digit in extract_color_code()");
	color_code = ft_atoi(str);
	return (color_code);
}

void	init_rgb(t_rgb *rgb, char *line)
{
	char	**rgb_arr;
	char	*rgb_line;

	rgb_line = ft_strtrim(line, "\t\n\v\f\r ");
	if (!rgb_line)
		handle_error("Failed malloc");
	rgb_arr = ft_split(rgb_line, ',');
	free(rgb_line);
	if (!rgb_arr)
		handle_error("Failed malloc");
	rgb->red = extract_color_code(rgb_arr[0]);
	rgb->green = extract_color_code(rgb_arr[1]);
	rgb->blue = extract_color_code(rgb_arr[2]);
	free(rgb_arr);
}

// void	init_colors(t_cub3d *cub3d, char *path)
// {
// 	int	fd;
// 	char	*curr_line;

// 	fd = open(path, O_RDONLY);
// 	if (fd < 0)
// 		handle_error("Failed to open file");
// 	while ((curr_line = get_next_line(fd)) != NULL)
// 	{
// 		skip_whitespace(&curr_line);
// 		if (curr_line[0] == 'F')
// 			init_rgb(&cub3d->graphics.floor, ++curr_line);
// 		else if (curr_line[0] == 'C')
// 			init_rgb(&cub3d->graphics.ceiling, ++curr_line);
// 	}
// }

mlx_image_t	*create_img(mlx_t *mlx, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	// printf("path:%s\n", path);
	texture = mlx_load_png(path);
	if (!texture)
		handle_error("Failed to load texture");
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (!image)
		handle_error("Failed to load image");
	return (image);
}

void	init_img(t_img *img, mlx_t *mlx, char *path)
{
	skip_whitespace(&path);
	if (!validate_file_extension(path, ".png"))
		handle_error("Wrong file extension must be .png");
	img->img = create_img(mlx, path);
	img->path = path;
}

void	init_graphics(t_cub3d *cub3d, int fd, char *path)
{
	int		config_count;
	char	*curr_line;
	char	*img_path;

	config_count = 0;
	while ((curr_line = get_next_line(fd)) != NULL && config_count < 6)
	{
		skip_whitespace(&curr_line);
		img_path = ft_strtrim(curr_line, "\t\n\v\f\r ");
		if (ft_strncmp(curr_line, "NO", 2) == 0)
		{
			init_img(&cub3d->graphics.north, cub3d->mlx, img_path + 2);
			config_count++;
		}
		else if (ft_strncmp(curr_line, "WE", 2) == 0)
			init_img(&cub3d->graphics.west, cub3d->mlx, img_path + 2);
		else if (ft_strncmp(curr_line, "EA", 2) == 0)
			init_img(&cub3d->graphics.east, cub3d->mlx, img_path + 2);
		else if (ft_strncmp(curr_line, "SO", 2) == 0)
			init_img(&cub3d->graphics.south, cub3d->mlx, img_path + 2);
		if (curr_line[0] == 'F')
			init_rgb(&cub3d->graphics.floor, ++curr_line);
		else if (curr_line[0] == 'C')
			init_rgb(&cub3d->graphics.ceiling, ++curr_line);
		free(img_path);
	}
}

void	init_cub3d(t_cub3d *cub3d, char *path)
{
	int	fd;

	cub3d->mlx = mlx_init(500, 500, "Cub3d", false);
	if (!cub3d->mlx)
		handle_error("MLX not initialized");
	fd = open(path, O_RDONLY);
		if (fd < 0)
			handle_error("Failed to open file");
	init_graphics(cub3d,fd, path);
	init_map(&cub3d->map, path);
	close (fd);
}
