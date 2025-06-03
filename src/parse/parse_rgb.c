
#include "cub3d.h"

static int	extract_color_code(char *str)
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

static void	parse_rgb(t_rgb *rgb, char *line)
{
	char	**rgb_arr;
	int		i;

	rgb_arr = ft_split(line, ',');
	if (!rgb_arr)
		handle_error("Failed malloc");
	rgb->red = extract_color_code(rgb_arr[0]);
	rgb->green = extract_color_code(rgb_arr[1]);
	rgb->blue = extract_color_code(rgb_arr[2]);
	validate_rgb(*rgb);
	i = 0;
	while (rgb_arr[i])
	{
		free(rgb_arr[i]);
		i++;
	}
	free(rgb_arr);
}

void	load_rgb(t_cub3d *cub3d, int *seen_flags, char *str)
{
	if (str[0] == 'F')
	{
		parse_rgb(&cub3d->graphics.floor, str + 1);
		seen_flags[F]++;
	}
	else if (str[0] == 'C')
	{
		parse_rgb(&cub3d->graphics.ceiling, str + 1);
		seen_flags[C]++;
	}
}