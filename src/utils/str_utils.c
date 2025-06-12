
#include "cub3d.h"

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

char	*clean_str(char *str)
{
	char	*new_str;

	skip_whitespace(&str);
	new_str = ft_strtrim(str, "\t\n\v\f\r ");
	return (new_str);
}

bool no_double_newline(char *str)
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
			return (false);
		start++;
	}
	return (true);
}