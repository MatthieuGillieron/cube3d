/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_window.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:06:51 by mg                #+#    #+#             */
/*   Updated: 2025/06/29 17:47:05 by maximemarti      ###   ########.fr       */
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
		game->keys.forward = 1;
	else if (keycode == 1)
		game->keys.backward = 1;
	else if (keycode == 0)
		game->keys.left = 1;
	else if (keycode == 2)
		game->keys.right = 1;
	else if (keycode == 123)
		game->keys.rotate_left = 1;
	else if (keycode == 124)
		game->keys.rotate_right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 13)
		game->keys.forward = 0;
	else if (keycode == 1)
		game->keys.backward = 0;
	else if (keycode == 0)
		game->keys.left = 0;
	else if (keycode == 2)
		game->keys.right = 0;
	else if (keycode == 123)
		game->keys.rotate_left = 0;
	else if (keycode == 124)
		game->keys.rotate_right = 0;
	return (0);
}

void	update_movement(t_game *game)
{
	if (game->keys.forward)
		move_forward(game);
	if (game->keys.backward)
		move_backward(game);
	if (game->keys.left)
		rotate_player(game, -1);
	if (game->keys.right)
		rotate_player(game, 1);
	if (game->keys.rotate_left)
		rotate_player(game, -1);
	if (game->keys.rotate_right)
		rotate_player(game, 1);
}
