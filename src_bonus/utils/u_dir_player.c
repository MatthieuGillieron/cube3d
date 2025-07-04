/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_dir_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:03:39 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/04 12:13:56 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	assign_direction(t_player *player)
{
	if (player->direction == 'N')
		player->angle = 3 * M_PI / 2;
	else if (player->direction == 'S')
		player->angle = M_PI / 2;
	else if (player->direction == 'E')
		player->angle = 0;
	else if (player->direction == 'W')
		player->angle = M_PI;
}

int	mouse_motion(int x, int y, t_game *game)
{
	static int	last_x = -1;
	int			dx;

	if (last_x != -1)
	{
		dx = x - last_x;
		game->player.angle += dx * MOUSE_SENS;
		if (game->player.angle >= 2 * M_PI)
			game->player.angle -= 2 * M_PI;
		if (game->player.angle < 0)
			game->player.angle += 2 * M_PI;
	}
	last_x = x;
	(void)y;
	return (0);
}
