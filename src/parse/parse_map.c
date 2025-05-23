
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
	if (!curr_line)
	{
		close(fd);
		handle_error("Config must be over map");
	}
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

size_t	get_max_line_length(char **grid)
{
	size_t	max = 0;
	size_t	len;
	int		i = 0;

	while (grid[i])
	{
		len = ft_strlen(grid[i]);
		if (len > max)
			max = len;
		i++;
	}
	return max;
}

void	fill_with_spaces(char **grid)
{
	size_t	max_len;
	int	i;
	char *filler;
	int	diff;

	max_len = get_max_line_length(grid);
	i = 0;
	while (grid[i])
	{
		
		if (ft_strlen(grid[i]) < max_len)
		{
			diff = max_len - ft_strlen(grid[i]);
			filler = malloc(sizeof(char) * diff + 1);
			ft_memset(filler, ' ', sizeof(char) * diff);
			filler[diff] = '\0';
			grid[i] = ft_strjoin(grid[i], filler);
			free(filler);
		}
		i++;
	}
}

static void	parse_grid(t_map *map, int fd)
{
	char	*combined_lines;
	
	combined_lines = read_all_lines(fd);
	if (!combined_lines || combined_lines[0] == '\0')
		handle_error("Failed read_all_lines in func create_grid");
	map->grid = ft_split(combined_lines, '\n');
	fill_with_spaces(map->grid);
	free(combined_lines);
	if (!map->grid)
		handle_error("Failed ft_split in func create_grid");
}

static void	parse_grid_size(t_map *map)
{
	int	height;
	int	width;

	height = 0;
	width = 0;
	while (map->grid[height] != NULL)
		height++;
	while (map->grid[0][width] != '\0')
		width++;
	map->grid_height = height;
	map->grid_width = width;
}

static void	parse_player_pos(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->grid_height)
	{
		x = 0;
		while (x < map->grid_width)
		{
			if (ft_strchr("NWES", map->grid[y][x]))
			{
				map->player_pos.x = x;
				map->player_pos.y = y;
				map->player_orientation = map->grid[y][x];
			}
			x++;
		}
		y++;
	}
}

void	parse_map(t_map *map, int fd)
{
	parse_grid(map, fd);
	parse_grid_size(map);
	parse_player_pos(map);
}
