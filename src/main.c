/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:20:08 by phhofman          #+#    #+#             */
/*   Updated: 2025/06/17 15:20:13 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_cub3d	cub3d;

	ft_memset(&cub3d, 0, sizeof(t_cub3d));
	if (argc != 2)
		handle_error(&cub3d, "Invalid number of arguments");
	if (!validate_file_extension(argv[1], ".cub"))
		handle_error(&cub3d, "File extension must be .cub");
	init_cub3d(&cub3d, argv[1]);
	mlx_close_hook(cub3d.mlx, handle_close, &cub3d);
	mlx_key_hook(cub3d.mlx, handle_keypress, &cub3d);
	mlx_resize_hook(cub3d.mlx, handle_resize, &cub3d);
	mlx_loop_hook(cub3d.mlx, game_loop, &cub3d);
	mlx_loop(cub3d.mlx);
	free_cub3d(&cub3d);
	mlx_terminate(cub3d.mlx);
	return (EXIT_SUCCESS);
}
