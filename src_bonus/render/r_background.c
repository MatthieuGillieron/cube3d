/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_background.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:41:59 by mg                #+#    #+#             */
/*   Updated: 2025/07/04 16:08:12 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include <math.h>

void	render_background(t_game *game)
{
	int			x;
	int			y;
	int			color;
	char		*dst;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	double		t;
	int			top_r;
	int			top_g;
	int			top_b;
	int			bot_r;
	int			bot_g;
	int			bot_b;
	double		f;
	int			r;
	int			g;
	int			b;

	floor_color = game->color.set_floor;
	ceiling_color = game->color.set_ceiling;
	t = fmod(get_time_seconds(), 10.0) / 10.0;
	top_r = (ceiling_color >> 16) & 0xFF;
	top_g = (ceiling_color >> 8) & 0xFF;
	top_b = ceiling_color & 0xFF;
	bot_r = 180 + 40 * sin(2 * M_PI * t + 2);
	bot_g = 180 + 30 * sin(2 * M_PI * t + 1);
	bot_b = 255;
	y = 0;
	while (y < game->win_h)
	{
		x = 0;
		if (y < game->win_h / 2)
		{
			f = (double)y / (game->win_h / 2);
			r = (int)(top_r * (1.0 - f) + bot_r * f);
			g = (int)(top_g * (1.0 - f) + bot_g * f);
			b = (int)(top_b * (1.0 - f) + bot_b * f);
			color = (r << 16) | (g << 8) | b;
		}
		else
		{
			f = (double)(y - game->win_h / 2) / (game->win_h / 2);
			top_r = (floor_color >> 16) & 0xFF;
			top_g = (floor_color >> 8) & 0xFF;
			top_b = floor_color & 0xFF;
			bot_r = (int)(top_r * 0.5 + 40 * sin(2 * M_PI * t));
			bot_g = (int)(top_g * 0.5 + 30 * sin(2 * M_PI * t + 1));
			bot_b = (int)(top_b * 0.5);
			r = (int)(top_r * (1.0 - f) + bot_r * f);
			g = (int)(top_g * (1.0 - f) + bot_g * f);
			b = (int)(top_b * (1.0 - f) + bot_b * f);
			color = (r << 16) | (g << 8) | b;
		}
		while (x < game->win_w)
		{
			dst = game->img.addr + (y * game->img.line_len + x * (game->img.bpp / 8));
			*(unsigned int *)dst = color;
			x++;
		}
		y++;
	}
}
