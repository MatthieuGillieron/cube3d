/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by mg                #+#    #+#             */
/*   Updated: 2025/01/02 00:00:00 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static int	validate_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		error_exit("Usage: ./cub3D <map.cub>");
		return (0);
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
	{
		error_exit("Map file must have .cub extension");
		return (0);
	}
	return (1);
}

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 1L << 17, close_window, game);
	mlx_loop_hook(game->mlx, render_frame, game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!validate_args(argc, argv))
		return (1);
	ft_bzero(&game, sizeof(t_game));
	if (!parse_file(argv[1], &game))
		error_exit("Failed to parse map file");
	if (!init_game(&game))
		error_exit("Failed to initialize game");
	setup_hooks(&game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}