/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_game.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:35:38 by mg                #+#    #+#             */
/*   Updated: 2025/06/29 17:23:34 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	init_game(t_game *game)
{
	game->win_w = 640;
	game->win_h = 480;
	game->key_w = 0;
	game->key_s = 0;
	game->key_a = 0;
	game->key_d = 0;
	game->key_left = 0;
	game->key_right = 0;
	game->map = game->map_data.map;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "cub3D");
	if (!game->win)
		return (0);
	if (!load_textures(game))
		return (0);
	return (1);
}
