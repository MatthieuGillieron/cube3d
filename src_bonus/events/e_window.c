/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_window.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:06:51 by mg                #+#    #+#             */
/*   Updated: 2025/07/04 12:14:01 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	get_facing_tile_coords(t_game *game, int *tx, int *ty)
{
	int		px;
	int		py;
	double	angle;
	int		dx;
	int		dy;

	px = (int)game->player.x;
	py = (int)game->player.y;
	angle = game->player.angle;
	dx = (int)round(cos(angle));
	dy = (int)round(sin(angle));
	*tx = px + dx;
	*ty = py + dy;
}

static void	try_open_door(t_game *game)
{
	int	tx;
	int	ty;

	get_facing_tile_coords(game, &tx, &ty);
	if (ty >= 0 && tx >= 0 && game->map[ty] && \
		tx < (int)ft_strlen(game->map[ty]))
	{
		if (game->map[ty][tx] == 'D')
			game->map[ty][tx] = '0';
	}
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W)
		game->keys.forward = 1;
	else if (keycode == KEY_S)
		game->keys.backward = 1;
	else if (keycode == KEY_A)
		game->keys.left = 1;
	else if (keycode == KEY_D)
		game->keys.right = 1;
	else if (keycode == KEY_LEFT)
		game->keys.rotate_left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.rotate_right = 1;
	else if (keycode == KEY_SPACE)
		try_open_door(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.forward = 0;
	else if (keycode == KEY_S)
		game->keys.backward = 0;
	else if (keycode == KEY_A)
		game->keys.left = 0;
	else if (keycode == KEY_D)
		game->keys.right = 0;
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
}
