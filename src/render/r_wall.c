/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_walls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:06 by mg                #+#    #+#             */
/*   Updated: 2025/06/26 15:43:32 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	draw_wall_slice(t_game *game, int x, t_ray_hit *hit)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		y;
	char	*dst;
	int		color;

	if (hit->distance <= 0)
		hit->distance = 0.1;

	line_height = (int)(game->win_h / hit->distance);

	draw_start = -line_height / 2 + game->win_h / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + game->win_h / 2;
	if (draw_end >= game->win_h)
		draw_end = game->win_h - 1;

	// Simulate light shading depending on side
	if (hit->side == 0)
		color = 0xFFFFFF; // bright
	else
		color = 0xAAAAAA; // dimmer

	y = draw_start;
	while (y <= draw_end)
	{
		dst = game->img.addr + (y * game->img.line_len + x * (game->img.bpp / 8));
		*(unsigned int *)dst = color;
		y++;
	}
}
