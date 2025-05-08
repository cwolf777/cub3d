
#include "cub3d.h"

static bool	is_seen_flags_full(int seen_flags[])
{
	int		i;

	i = 0;
	while (i < SEEN_FLAGS_LENGTH)
	{
		if (seen_flags[i] == 0)
			return (false);
		i++;
	}
	return (true);
}

void	parse_graphics(t_cub3d *cub3d, int fd)
{
	int		i;
	char	*curr_line;
	char	*input_str;
	int		seen_flags[SEEN_FLAGS_LENGTH];

	ft_memset(seen_flags, 0, sizeof(int) * SEEN_FLAGS_LENGTH);
	curr_line = get_next_line(fd);
	while (curr_line != NULL && !is_seen_flags_full(seen_flags))
	{
		input_str = clean_str(curr_line);
		free(curr_line);
		load_texture(cub3d, seen_flags, input_str);
		load_rgb(cub3d, seen_flags, input_str);
		curr_line = get_next_line(fd);
		// free(input_str);
	}
	i = 0;
	while (i < SEEN_FLAGS_LENGTH)
	{
		if (seen_flags[i] != 1)
			handle_error("Wrong config for graphics");
		i++;
	}
}

