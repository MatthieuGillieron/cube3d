/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:15:08 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/26 15:44:23 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	main(int ac, char **av)
{
	char		**files;
	t_map_data	map;
	t_game		game;

	ft_bzero(&map, sizeof(map));
	ft_bzero(&game, sizeof(game));
	if (ac != 2)
		return (1);
	files = open_map(av[1]);
	if (!files)
		return (1);
	if (check_file(files, &map))
		return (1);
	game.color.set_floor = map.colors.set_floor;
	game.color.set_ceiling = map.colors.set_ceiling;
	game.player = map.player;
	game.map = map.map;
	if (!init_game(&game))
		return (1);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop_hook(game.mlx, render_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
