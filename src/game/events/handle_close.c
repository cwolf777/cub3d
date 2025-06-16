/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:25:30 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/16 16:25:40 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_close(void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	mlx_terminate(cub3d->mlx);
	free_cub3d(cub3d);
	exit(EXIT_SUCCESS);
}
