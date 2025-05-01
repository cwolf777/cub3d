
#include "cub3d.h"

static char	*read_all_lines(int fd)
{
	char	*curr_line;
	char	*combined_lines;
	char	*temp;

	combined_lines = ft_strdup("");
	if (!combined_lines)
	{
		close(fd);
		handle_error("Malloc failed in func: read_all_lines");
	}
	curr_line = get_next_line(fd);
	while (curr_line != NULL)
	{
		temp = combined_lines;
		combined_lines = ft_strjoin(combined_lines, curr_line);
		free(temp);
		free(curr_line);
		if (!combined_lines)
		{
			close(fd);
			handle_error("Malloc failed in func: read_all_lines");
		}
		curr_line = get_next_line(fd);
	}
	return (combined_lines);
}

static void	parse_grid(t_map *map, int fd)
{
	char	*combined_lines;
	
	combined_lines = read_all_lines(fd);
	if (!combined_lines || combined_lines[0] == '\0')
		handle_error("Failed read_all_lines in func create_grid");
	map->grid = ft_split(combined_lines, '\n');
	free(combined_lines);
	if (!map->grid)
		handle_error("Failed ft_split in func create_grid");
}

static void	parse_map_size(t_map *map)
{
	int	height;
	int	width;

	height = 0;
	width = 0;
	while (map->grid[height] != NULL)
		height++;
	while (map->grid[0][width] != '\0')
		width++;
	map->height = height;
	map->width = width;
}

void	parse_map(t_map *map, int fd)
{
	parse_grid(map, fd);
	parse_map_size(map);
}
