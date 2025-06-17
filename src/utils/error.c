/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:14:11 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 15:14:16 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_error(t_cub3d *cub3d, char *error_msg)
{
	ft_printf("Error\n");
	ft_printf("%s\n", error_msg);
	if (cub3d)
		free_cub3d(cub3d);
	exit(EXIT_FAILURE);
}
