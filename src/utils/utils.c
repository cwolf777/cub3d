
#include "cub3d.h"

void	skip_whitespace(char **str)
{
	while (ft_strchr("\t\n\v\f\r ", **str) != NULL && **str != '\0')
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

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
}