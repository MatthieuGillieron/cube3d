/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_dir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:03:39 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/24 11:03:55 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	assign_direction(t_player *player)
{
	if (player->direction == 'N')
    	player->dir = 270;
	else if (player->direction == 'S')
		player->dir = 90;
	else if (player->direction == 'E')
		player->dir = 0;
	else if (player->direction == 'W')
		player->dir = 180;
}
