
#include "cub3d.h"

bool	validate_file_extension(char *path, char *extension)
{
	int		i;
	int		j;
	char	*filename;

	filename = ft_strrchr(path, '/');
	if (!filename)
		filename = path;
	else
		filename++;
	i = ft_strlen(filename) - 1;
	j = ft_strlen(extension) - 1;
	if (i == j)
		return (false);
	while (j >= 0)
	{
		if (filename[i] != extension[j])
			return (false);
		i--;
		j--;
	}
	return (true);
}


bool	validate_player(t_map map)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = 0;
	print_grid(map.grid);
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			printf("%c", map.grid[y][x]);
			if (ft_strchr("NWES", map.grid[y][x]))
			{
				// printf("c: %c\n", map.grid[y][x]);
				player_count++;
			}
			x++;
		}
		printf("\n");
		y++;
	}
	if (player_count == 1)
		return (true);
	return (false);
}
