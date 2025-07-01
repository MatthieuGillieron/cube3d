/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_move_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:57:11 by mg                #+#    #+#             */
/*   Updated: 2025/07/01 11:28:45 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	int		max_y;
	int		max_x;

	new_x = game->player.x + cos(game->player.angle) * MOVE_SPEED;
	new_y = game->player.y + sin(game->player.angle) * MOVE_SPEED;
	max_y = 0;
	max_x = 0;
	while (game->map[max_y])
		max_y++;
	while (max_y > 0 && game->map[0][max_x])
		max_x++;
	if (new_x >= 0 && new_y >= 0 && (int)new_y < max_y && (int)new_x \
	< max_x && game->map[(int)new_y][(int)new_x] != '\0')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	int		max_y;
	int		max_x;

	new_x = game->player.x - cos(game->player.angle) * MOVE_SPEED;
	new_y = game->player.y - sin(game->player.angle) * MOVE_SPEED;
	max_y = 0;
	max_x = 0;
	while (game->map[max_y])
		max_y++;
	while (max_y > 0 && game->map[0][max_x])
		max_x++;
	if (new_x >= 0 && new_y >= 0 && (int)new_y < max_y && (int)new_x \
	< max_x && game->map[(int)new_y][(int)new_x] != '\0')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}
/*
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + cos(game->player.angle - M_PI / 2) * MOVE_SPEED;
	new_y = game->player.y + sin(game->player.angle - M_PI / 2) * MOVE_SPEED;
	if (game->map[(int)new_y][(int)new_x] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + cos(game->player.angle + M_PI / 2) * MOVE_SPEED;
	new_y = game->player.y + sin(game->player.angle + M_PI / 2) * MOVE_SPEED;
	if (game->map[(int)new_y][(int)new_x] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}*/
