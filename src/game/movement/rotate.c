/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:30:55 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/16 16:32:07 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_cub3d *cub3d, double delta_time)
{
	cub3d->player.angle -= PLAYER_ROT_SPEED * delta_time;
	if (cub3d->player.angle < 0)
		cub3d->player.angle += 2 * M_PI;
}

void	rotate_right(t_cub3d *cub3d, double delta_time)
{
	cub3d->player.angle += PLAYER_ROT_SPEED * delta_time;
	if (cub3d->player.angle > 2 * M_PI)
		cub3d->player.angle -= 2 * M_PI;
}
