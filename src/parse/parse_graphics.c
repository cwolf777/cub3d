
#include "cub3d.h"

static bool	is_graphics_full(int graphics[])
{
	int		i;

	i = 0;
	while (i < GRAPHICS_LENGTH)
	{
		if (graphics[i] == 0)
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
	int		graphics[GRAPHICS_LENGTH];

	ft_memset(graphics, 0, sizeof(int) * GRAPHICS_LENGTH);
	curr_line = get_next_line(fd);
	while (curr_line != NULL && !is_graphics_full(graphics))
	{
		input_str = clean_str(curr_line);
		free(curr_line);
		load_texture(cub3d, graphics, input_str);
		load_rgb(cub3d, graphics, input_str);
		curr_line = get_next_line(fd);
		free(input_str);
	}
	i = 0;
	if (curr_line)
		free(curr_line);
	while (i < GRAPHICS_LENGTH)
	{
		if (graphics[i] != 1)
			handle_error(cub3d, "Wrong config for graphics");
		i++;
	}
}
