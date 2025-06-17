/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:24:57 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 14:44:54 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*read_all_lines(t_cub3d *cub3d, int fd)
{
	char	*curr_line;
	char	*combined_lines;
	char	*temp;

	combined_lines = ft_strdup("");
	if (!combined_lines)
		handle_error(cub3d, "Malloc failed in func: read_all_lines");
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
			handle_error(cub3d, "Malloc failed in func: read_all_lines");
		curr_line = get_next_line(fd);
	}
	return (combined_lines);
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

void	parse_map(t_cub3d *cub3d, t_map *map, int fd)
{
	parse_grid(cub3d, map, fd);
	parse_grid_size(map);
	parse_player_index(map);
}
