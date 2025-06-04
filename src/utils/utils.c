
#include "cub3d.h"

double	degree_to_rad(int degree)
{
	return (degree * M_PI / 180);
}

bool	is_white_space(char c)
{
	if (ft_strchr("\t\n\v\f\r ", c))
		return (true);
	return (false);
}

void	skip_whitespace(char **str)
{
	while (is_white_space(**str) && **str != '\0')
		(*str)++;
}

bool	is_valid_digit_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	handle_error(char *error_msg)
{
	ft_printf("Error\n");
	ft_printf("%s\n", error_msg);
	exit(EXIT_FAILURE);
}

void	free_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i] != NULL)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

char	*clean_str(char *str)
{
	char	*new_str;

	skip_whitespace(&str);
	new_str = ft_strtrim(str, "\t\n\v\f\r ");
	return (new_str);
}

char	**copy_grid(t_cub3d *cub3d, t_map map)
{
	char	**new_grid;
	int		i;

	i = 0;
	new_grid = malloc(sizeof(char *) * (map.grid_height + 1));
	if (!new_grid)
		handle_close(cub3d, "Malloc failed in func: copy_map");
	while (map.grid[i] != NULL)
	{
		new_grid[i] = ft_strdup(map.grid[i]);
		if (!new_grid[i])
			handle_close(cub3d, "Malloc failed in func: copy_map");
		i++;
	}
	new_grid[i] = NULL;
	return (new_grid);
}

uint32_t rgb_to_color(t_rgb color)
{
	uint32_t r = (uint32_t)(color.red & 0xFF) << 24;
	uint32_t g = (uint32_t)(color.green & 0xFF) << 16;
	uint32_t b = (uint32_t)(color.blue & 0xFF) << 8;
	uint32_t a = 0xFF;

	return r | g | b | a;
}

t_point world_to_minimap(t_cub3d *cub3d, double world_x, double world_y)
{
	t_point	point;
	double	offset_x;
	double	offset_y;

	offset_x = cub3d->player.pixel_pos.x - (MINIMAP_WIDTH / 2);
	offset_y = cub3d->player.pixel_pos.y - (MINIMAP_HEIGHT / 2);
	point.x = (int)(world_x - offset_x);
	point.y = (int)(world_y - offset_y);
	return (point);
}
