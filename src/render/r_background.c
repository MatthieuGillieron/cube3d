/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_background.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:41:59 by mg                #+#    #+#             */
/*   Updated: 2025/06/26 15:42:47 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	render_background(t_game *game)
{
	int		x;
	int		y;
	int		color;
	char	*dst;

	y = 0;
	while (y < game->win_h)
	{
		x = 0;
		while (x < game->win_w)
		{
			if (y < game->win_h / 2)
				color = game->color.set_ceiling;
			else
				color = game->color.set_floor;
			dst = game->img.addr
				+ (y * game->img.line_len + x * (game->img.bpp / 8));
			*(unsigned int *)dst = color;
			x++;
		}
		y++;
	}
}
