/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_move_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:57:11 by mg                #+#    #+#             */
/*   Updated: 2025/06/29 17:45:52 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + cos(game->player.angle) * 0.05;
	new_y = game->player.y + sin(game->player.angle) * 0.05;
	if (game->map[(int)new_y][(int)new_x] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - cos(game->player.angle) * 0.05;
	new_y = game->player.y - sin(game->player.angle) * 0.05;
	if (game->map[(int)new_y][(int)new_x] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + cos(game->player.angle - M_PI / 2) * 0.05;
	new_y = game->player.y + sin(game->player.angle - M_PI / 2) * 0.05;
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

	new_x = game->player.x + cos(game->player.angle + M_PI / 2) * 0.05;
	new_y = game->player.y + sin(game->player.angle + M_PI / 2) * 0.05;
	if (game->map[(int)new_y][(int)new_x] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}
