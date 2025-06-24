/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:15:08 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/24 11:19:45 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

 int	init_game(t_game *game)
{
	game->win_w = 640;
	game->win_h = 480;

	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "cub3D");
	if (!game->win)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	char		**files;
	t_map_data	map = {0};
	t_game		game;

	if (ac != 2)
		return (1);
	files = open_map(av[1]);
	if (check_file(files, map))
		return (1);
	printf("ok\n");
	if (!init_game(&game))
		return (1);
	mlx_loop(game.mlx);
	return (0);
}
