/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:15:08 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/24 19:48:46 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	render_background(t_game *game)
{
	int		x;
	int		y;
	int		color;
	char	*dst;

	y = 0;
	while (y < game->win_h)
	{
		x = 0;
		while (x < game->win_w)
		{
			if (y < game->win_h / 2)
				color = game->color.set_ceiling;
			else
				color = game->color.set_floor;
			dst = game->img.addr
				+ (y * game->img.line_len + x * (game->img.bpp / 8));
			*(unsigned int *)dst = color;
			x++;
		}
		y++;
	}
}

int	render_loop(t_game *game)
{
	game->img.img = mlx_new_image(
			game->mlx, game->win_w, game->win_h);
	game->img.addr = mlx_get_data_addr(
			game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	render_background(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	mlx_destroy_image(game->mlx, game->img.img);
	return (0);
}

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
	mlx_loop_hook(game.mlx, render_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
