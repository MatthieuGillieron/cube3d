/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_minimap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:54:13 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/02 09:05:39 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	draw_pixel(t_game *game, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= game->win_w || y < 0 || y >= game->win_h)
		return ;
	dst = game->img.addr + (y * game->img.line_len + x * (game->img.bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_circle(t_circle_params *circle)
{
	int	x;
	int	y;

	y = -circle->r;
	while (y <= circle->r)
	{
		x = -circle->r;
		while (x <= circle->r)
		{
			if (x * x + y * y <= circle->r * circle->r)
				draw_pixel(circle->game, circle->cx + x, circle->cy
					+ y, circle->color);
			x++;
		}
		y++;
	}
}

int	get_direction(int start, int end)
{
	if (start < end)
		return (1);
	return (-1);
}

void	draw_line(t_line_params *line)
{
	int	dx;
	int	dy;
	int	err;
	int	e2;

	dx = abs(line->x1 - line->x0);
	dy = -abs(line->y1 - line->y0);
	err = dx + dy;
	while (1)
	{
		draw_pixel(line->game, line->x0, line->y0, line->color);
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			line->x0 += get_direction(line->x0, line->x1);
		}
		if (e2 <= dx)
		{
			err += dx;
			line->y0 += get_direction(line->y0, line->y1);
		}
	}
}

void	draw_player_minimap(t_minimap *mm)
{
	int				player_px;
	int				player_py;
	int				dir_len;
	t_line_params	line;
	t_circle_params	circle;

	player_px = mm->margin + (int)(mm->game->player.x * mm->cell);
	player_py = mm->margin + (int)(mm->game->player.y * mm->cell);
	circle.game = mm->game;
	circle.cx = player_px;
	circle.cy = player_py;
	circle.r = mm->cell / 3;
	circle.color = COLOR_PLAYER;
	draw_circle(&circle);
	dir_len = (int)(mm->cell * 1.2);
	line.game = mm->game;
	line.x0 = player_px;
	line.y0 = player_py;
	line.x1 = player_px + (int)(cos(mm->game->player.angle) * dir_len);
	line.y1 = player_py + (int)(sin(mm->game->player.angle) * dir_len);
	line.color = COLOR_DIR;
	draw_line(&line);
}
