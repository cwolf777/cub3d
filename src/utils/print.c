/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:15:46 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 15:16:07 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i] != NULL)
	{
		ft_printf("%s\n", grid[i]);
		i++;
	}
}

void	print_rgb(const char *label, t_rgb color)
{
	printf("	%s: [%d,%d,%d]\n", label, color.red, color.green, color.blue);
}

// void	print_cub3d_info(t_cub3d *cub)
// {
// 	printf("=========== CUB3D INFO ===========\n");

// 	printf("Graphics:\n");
// 	printf("	North: %s\n", cub->graphics.north.path);
// 	printf("	South: %s\n", cub->graphics.south.path);
// 	printf("	East:  %s\n", cub->graphics.east.path);
// 	printf("	West:  %s\n", cub->graphics.west.path);
// 	print_rgb("Floor Color", cub->graphics.floor);
// 	print_rgb("Ceiling Color", cub->graphics.ceiling);

// 	printf("Player:\n");
// 	printf("	Position:	x = %d, y = %d\n", (int)cub->player.pixel_pos.x,
// 					(int)cub->player.pixel_pos.y);
// 	printf("	Angle:		%f rad (%.2f°)\n", cub->player.angle,
// 						cub->player.angle * (180.0 / M_PI));
// 	printf("	Speed:		%d\n", cub->player.speed);
// 	printf("	Rot. Speed:  %f rad/frame (%.2f°)\n", cub->player.rot_speed,
// 				cub->player.rot_speed * (180.0 / M_PI));
// 	printf("	Size:	%d px\n", cub->player.size);

// 	printf("Map:\n");
// 	printf("	Dimensions:  width = %d, height = %d\n", cub->map.grid_width,
// 				cub->map.grid_height);
// 	printf("	PIXELS:			width = %d, height = %d\n", MINIMAP_WIDTH,
// 							MINIMAP_HEIGHT);
// 	printf("	Tile Size:   %d px\n", TILE_SIZE);
// 	printf("	Player Start Index: x = %d, y = %d (orientation: '%c')\n",
// 			(int)cub->map.player_index.x,
// 			(int)cub->map.player_index.y,
// 			cub->map.player_orientation);
// 	printf("Grid:\n");
// 	print_grid(cub->map.grid);

// 	printf("=========== END INFO ============\n");
// }
