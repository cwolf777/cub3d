/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:32:31 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/16 16:34:15 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_cub3d *cub3d, double *move_x, double *move_y,
	double delta_time)
{
	*move_x += cos(cub3d->player.angle) * PLAYER_SPEED * delta_time;
	*move_y += sin(cub3d->player.angle) * PLAYER_SPEED * delta_time;
}

void	move_backward(t_cub3d *cub3d, double *move_x, double *move_y,
	double delta_time)
{
	*move_x -= cos(cub3d->player.angle) * PLAYER_SPEED * delta_time;
	*move_y -= sin(cub3d->player.angle) * PLAYER_SPEED * delta_time;
}

void	move_left(t_cub3d *cub3d, double *move_x, double *move_y,
	double delta_time)
{
	*move_x += cos(cub3d->player.angle - M_PI_2) * PLAYER_SPEED * delta_time;
	*move_y += sin(cub3d->player.angle - M_PI_2) * PLAYER_SPEED * delta_time;
}

void	move_right(t_cub3d *cub3d, double *move_x, double *move_y,
	double delta_time)
{
	*move_x += cos(cub3d->player.angle + M_PI_2) * PLAYER_SPEED * delta_time;
	*move_y += sin(cub3d->player.angle + M_PI_2) * PLAYER_SPEED * delta_time;
}
