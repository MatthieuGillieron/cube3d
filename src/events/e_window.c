/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_window.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:06:51 by mg                #+#    #+#             */
/*   Updated: 2025/06/29 17:27:19 by maximemarti      ###   ########.fr       */
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
		rotate_player(game, -1);
	else if (keycode == 2)
		rotate_player(game, 1);
	else if (keycode == 123)
		rotate_player(game, -1);
	else if (keycode == 124)
		rotate_player(game, 1);
	return (0);
}
