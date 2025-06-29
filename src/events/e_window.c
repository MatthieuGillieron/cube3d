/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_window.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:06:51 by mg                #+#    #+#             */
/*   Updated: 2025/06/29 15:29:08 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 53)
		close_window(game);
	else if (keycode == 13)
		move_forward(game);
	else if (keycode == 1)
		move_backward(game);
	else if (keycode == 0)
		move_left(game);
	else if (keycode == 2)
		move_right(game);
	else if (keycode == 123)
		rotate_player(game, -1);
	else if (keycode == 124)
		rotate_player(game, 1);
	return (0);
}
