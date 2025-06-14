
#include "cub3d.h"

static char	*read_all_lines(t_cub3d *cub3d, int fd)
{
	char	*curr_line;
	char	*combined_lines;
	char	*temp;

	combined_lines = ft_strdup("");
	if (!combined_lines)
	{
		handle_error(cub3d, "Malloc failed in func: read_all_lines");
	}
	curr_line = get_next_line(fd);
	if (!curr_line)
	{
		free(combined_lines);
		handle_error(cub3d, "Config must be over map");
	}
	while (curr_line != NULL)
	{
		temp = combined_lines;
		combined_lines = ft_strjoin(combined_lines, curr_line);
		free(temp);
		free(curr_line);
		if (!combined_lines)
		{
			handle_error(cub3d, "Malloc failed in func: read_all_lines");
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

bool	fill_with_spaces(char **grid) //alte grid in temp und dann temp freen 
{
	size_t	max_len;
	int	i;
	char *filler;
	int	diff;
	char *temp;


	max_len = get_max_line_length(grid);
	i = 0;
	while (grid[i])
	{
		if (ft_strlen(grid[i]) < max_len)
		{
			temp = grid[i];
			diff = max_len - ft_strlen(grid[i]);
			filler = malloc(sizeof(char) * diff + 1);
			if (!filler)
				return (false);
			ft_memset(filler, ' ', sizeof(char) * diff);
			filler[diff] = '\0';
			grid[i] = ft_strjoin(temp, filler);
			free(temp);
			if (!grid[i])
			{
				free(filler);
				return (false);
			}
			free(filler);
		}
		i++;
	}
	return(true);
}

static void	parse_grid(t_cub3d *cub3d, t_map *map, int fd)
{
	char	*combined_lines;
	
	combined_lines = read_all_lines(cub3d, fd);
	if (!combined_lines || combined_lines[0] == '\0')
		handle_error(cub3d, "Failed read_all_lines in func create_grid");
	if (!no_double_newline(combined_lines))
	{
		free(combined_lines);
		handle_error(cub3d, "Invalid map");
	}
	map->grid = ft_split(combined_lines, '\n');
	if (!map->grid || !map->grid[0])
	{
		free(combined_lines);
		handle_error(cub3d, "Wrong location of map");
	}
	if (!fill_with_spaces(map->grid))
	{
		free(combined_lines);
		handle_error(cub3d, "Allocation failed");
	}
	free(combined_lines);
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

static void	parse_player_index(t_map *map)
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
				map->player_index.x = x;
				map->player_index.y = y;
				map->player_orientation = map->grid[y][x];
			}
			x++;
		}
		y++;
	}
}

void	parse_map(t_cub3d *cub3d, t_map *map, int fd)
{
	parse_grid(cub3d,map, fd);
	parse_grid_size(map);
	parse_player_index(map);
}
