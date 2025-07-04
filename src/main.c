/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:15:08 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/04 12:32:04 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	validate_args(int ac, char **av)
{
	int	len;

	if (ac != 2)
	{
		printf("Error\nUsage: %s <map_file.cub>\n", av[0]);
		exit(1);
	}
	len = ft_strlen(av[1]);
	if (len < 4 || ft_strncmp(av[1] + len - 4, ".cub", 4) != 0)
	{
		printf("Error\nInvalid map extension\n");
		exit(1);
	}
}

static char	**load_and_check_map(char *filename, t_map_data *map)
{
	char	**files;

	files = open_map(filename);
	if (!files)
	{
		printf("Error\nCannot open map file: %s\n", filename);
		exit(1);
	}
	if (check_file(files, map))
		exit(1);
	return (files);
}

void	game_setup(int ac, char **av, t_game *game)
{
	char		**files;
	t_map_data	map;

	ft_bzero(&map, sizeof(map));
	ft_bzero(game, sizeof(*game));
	validate_args(ac, av);
	files = load_and_check_map(av[1], &map);
	game->map_data = map;
	game->color.set_floor = map.colors.set_floor;
	game->color.set_ceiling = map.colors.set_ceiling;
	game->player = map.player;
	game->map = map.map;
	if (!init_game(game))
	{
		printf("Error\nFailed to initialize graphics or window.\n");
		exit(1);
	}
}

void	game_loop(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_loop_hook(game->mlx, render_loop, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	game;

	game_setup(ac, av, &game);
	game_loop(&game);
	return (0);
}
