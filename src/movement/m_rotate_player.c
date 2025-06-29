/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_rotate_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:59:21 by mg                #+#    #+#             */
/*   Updated: 2025/06/29 16:18:01 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	rotate_player(t_game *game, int direction)
{
	if (direction == 1)
		game->player.angle += 0.1;
	else
		game->player.angle -= 0.1;
	if (game->player.angle >= 2 * M_PI)
		game->player.angle -= 2 * M_PI;
	if (game->player.angle < 0)
		game->player.angle += 2 * M_PI;
}
