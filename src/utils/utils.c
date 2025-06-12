
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
		handle_error(cub3d, "Malloc failed in func: copy_map");
	while (map.grid[i] != NULL)
	{
		new_grid[i] = ft_strdup(map.grid[i]);
		if (!new_grid[i])
			handle_error(cub3d, "Malloc failed in func: copy_map");
		i++;
	}
	new_grid[i] = NULL;
	return (new_grid);
}

uint32_t rgb_to_color(t_rgb color)
{
	uint32_t r;
	uint32_t b;
	uint32_t g;
	uint32_t a;

	r = (uint32_t)(color.red & 0xFF) << 24;
	g = (uint32_t)(color.green & 0xFF) << 16;
	b = (uint32_t)(color.blue & 0xFF) << 8;
	a = 0xFF;
	return (r | g | b | a);
}

t_point world_coord_to_minimap_coord(t_cub3d cub3d, double world_x, double world_y)
{
	t_point	point;
	double	offset_x;
	double	offset_y;

	offset_x = cub3d.player.pixel_pos.x - (MINIMAP_WIDTH / 2);
	offset_y = cub3d.player.pixel_pos.y - (MINIMAP_HEIGHT / 2);
	point.x = world_x - offset_x;
	point.y = world_y - offset_y;
	return (point);
}

bool no_double_newline(const char *str)
{
	int start;
	int end;

	end = ft_strlen(str);
	start = 0;
	while (str[start] == '\n')
		start++;
	while (end > start && str[end - 1] == '\n')
		end--;
	while (start < end - 1)
	{
		if (str[start] == '\n' && str[start + 1] == '\n')
			return false;
		start++;
	}
	return true;
}
bool is_inside_image(mlx_image_t *img, int x, int y)
{
	if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
		return (true);
	return (false);
}

uint32_t	convert_abgr_to_rgba(uint32_t abgr)
{
	uint8_t	a;
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;

	r = abgr & 0xFF;
	g = (abgr >> 8) & 0xFF;
	b = (abgr >> 16) & 0xFF;
	a = (abgr >> 24) & 0xFF;

	return ((r << 24) | (g << 16) | (b << 8) | a);
}
