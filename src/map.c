
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

void	init_map_size(t_map *map)
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

char	**create_grid(char *path)
{
	int		fd;
	char	*combined_lines;
	char	**map;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		handle_error("Failed to open file");
	while ((line = get_next_line(fd)) != NULL)
	{
		
	}
	combined_lines = read_all_lines(fd);
	close(fd);
	if (!combined_lines || combined_lines[0] == '\0')
		handle_error("Failed read_all_lines in func create_map");
	map = ft_split(combined_lines, '\n');
	free(combined_lines);
	if (!map)
		handle_error("Failed ft_split in func create_map");
	return (map);
}