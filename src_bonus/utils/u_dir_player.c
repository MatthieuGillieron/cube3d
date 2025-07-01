/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_dir_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:03:39 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/29 09:48:17 by maximemarti      ###   ########.fr       */
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
