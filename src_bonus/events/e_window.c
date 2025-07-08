/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_window.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:06:51 by mg                #+#    #+#             */
/*   Updated: 2025/07/04 15:59:32 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include <string.h>
#include <sys/time.h>

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

double	get_time_seconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

static void	register_open_door(t_game *game, int tx, int ty)
{
	if (game->open_door_count >= 32)
		return ;
	game->open_doors[game->open_door_count].x = tx;
	game->open_doors[game->open_door_count].y = ty;
	game->open_doors[game->open_door_count].open_time = get_time_seconds();
	game->open_door_count++;
}

static int	is_door_already_opened(t_game *game, int tx, int ty)
{
	int	i;

	i = 0;
	while (i < game->open_door_count)
	{
		if (game->open_doors[i].x == tx && game->open_doors[i].y == ty)
			return (1);
		i++;
	}
	return (0);
}

static void	try_open_door(t_game *game)
{
	int	tx;
	int	ty;

	get_facing_tile_coords(game, &tx, &ty);
	if (ty < 0 || tx < 0 || !game->map[ty] || \
		tx >= (int)ft_strlen(game->map[ty]))
		return ;
	if (game->map[ty][tx] != 'D')
		return ;
	game->map[ty][tx] = '0';
	if (!is_door_already_opened(game, tx, ty))
		register_open_door(game, tx, ty);
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
