
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

char	**copy_grid(t_map map)
{
	char	**new_grid;
	int		i;

	i = 0;
	new_grid = malloc(sizeof(char *) * (map.height + 1));
	if (!new_grid)
		handle_error("Malloc failed in func: copy_map");
	while (map.grid[i] != NULL)
	{
		new_grid[i] = ft_strdup(map.grid[i]);
		if (!new_grid[i])
			handle_error("Malloc failed in func: copy_map");
		i++;
	}
	new_grid[i] = NULL;
	return (new_grid);
}

