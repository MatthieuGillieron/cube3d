/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:30:00 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/30 11:30:00 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube3d.h"

void	game_setup(int ac, char **av, t_game *game)
{
	char		**files;
	t_map_data	map;

	printf("DEBUG: Starting game_setup\n");
	ft_bzero(&map, sizeof(map));
	ft_bzero(game, sizeof(*game));
	if (ac != 2)
		exit(1);
	printf("DEBUG: Opening map file\n");
	files = open_map(av[1]);
	if (!files)
		exit(1);
	printf("DEBUG: Checking file\n");
	if (check_file(files, &map))
		exit(1);
	printf("DEBUG: File check passed\n");
	game->map_data = map;
	game->color.set_floor = map.colors.set_floor;
	game->color.set_ceiling = map.colors.set_ceiling;
	game->player = map.player;
	game->map = map.map;
	printf("DEBUG: Initializing game\n");
	if (!init_game(game))
		exit(1);
	printf("DEBUG: Game initialized successfully\n");
}

void	game_loop(t_game *game)
{
	printf("DEBUG: Starting game loop\n");
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_hook(game->win, 2, 0, key_press, game);
	mlx_hook(game->win, 3, 0, key_release, game);
	mlx_hook(game->win, 6, 0, mouse_motion, game);
	mlx_loop_hook(game->mlx, render_loop, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	game;

	printf("DEBUG: Program started\n");
	game_setup(ac, av, &game);
	game_loop(&game);
	return (0);
}