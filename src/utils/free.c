/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:14:48 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 15:14:50 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_images(t_cub3d *cub3d)
{
	if (cub3d->player.img)
		mlx_delete_image(cub3d->mlx, cub3d->player.img);
	if (cub3d->ray_caster.img)
		mlx_delete_image(cub3d->mlx, cub3d->ray_caster.img);
	if (cub3d->map.img)
		mlx_delete_image(cub3d->mlx, cub3d->map.img);
	if (cub3d->view_img)
		mlx_delete_image(cub3d->mlx, cub3d->view_img);
	if (cub3d->graphics.north.img)
		mlx_delete_image(cub3d->mlx, cub3d->graphics.north.img);
	if (cub3d->graphics.south.img)
		mlx_delete_image(cub3d->mlx, cub3d->graphics.south.img);
	if (cub3d->graphics.west.img)
		mlx_delete_image(cub3d->mlx, cub3d->graphics.west.img);
	if (cub3d->graphics.east.img)
		mlx_delete_image(cub3d->mlx, cub3d->graphics.east.img);
}

void	free_cub3d(t_cub3d *cub3d)
{
	get_next_line(-1);
	if (cub3d->fd != -1)
		close(cub3d->fd);
	free_images(cub3d);
	if (cub3d->map.grid)
		free_grid(cub3d->map.grid);
	if (cub3d->graphics.north.path)
		free(cub3d->graphics.north.path);
	if (cub3d->graphics.south.path)
		free(cub3d->graphics.south.path);
	if (cub3d->graphics.west.path)
		free(cub3d->graphics.west.path);
	if (cub3d->graphics.east.path)
		free(cub3d->graphics.east.path);
}

void	free_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i] != NULL)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}
