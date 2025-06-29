/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:23:57 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 14:24:06 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_cub3d(t_cub3d *cub3d, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		handle_error(cub3d, "Failed to open file");
	cub3d->fd = fd;
	parse_graphics(cub3d, fd);
	parse_map(cub3d, &cub3d->map, fd);
	close(fd);
	cub3d->fd = -1;
}
