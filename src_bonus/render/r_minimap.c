/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_minimap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:49:23 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/02 09:05:17 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	draw_minimap_cell(t_minimap *mm, int map_x, int map_y,
			unsigned int color)
{
	int	px;
	int	py;

	py = 0;
	while (py < mm->cell)
	{
		px = 0;
		while (px < mm->cell)
		{
			draw_pixel(mm->game,
				mm->margin + map_x * mm->cell + px,
				mm->margin + map_y * mm->cell + py,
				color);
			px++;
		}
		py++;
	}
}

static void	draw_single_minimap_cell(t_minimap *mm, int x, int y)
{
	unsigned int	color;
	int				row_len;

	row_len = ft_strlen(mm->game->map[y]);
	if (x < row_len)
	{
		if (mm->game->map[y][x] == '1')
			color = COLOR_WALL;
		else if (mm->game->map[y][x] == '0')
			color = COLOR_EMPTY;
		else
			color = COLOR_WALL;
	}
	else
		color = COLOR_WALL;
	draw_minimap_cell(mm, x, y, color);
}

static void	draw_minimap_cells(t_minimap *mm)
{
	int	map_y;
	int	map_x;

	map_y = 0;
	while (mm->game->map[map_y])
	{
		map_x = 0;
		while (map_x < mm->width)
		{
			draw_single_minimap_cell(mm, map_x, map_y);
			map_x++;
		}
		map_y++;
	}
}

static void	draw_minimap_background(t_minimap *mm)
{
	int	px;
	int	py;
	int	mm_w;
	int	mm_h;
	int	x;

	mm_w = mm->width * mm->cell;
	mm_h = mm->height * mm->cell;
	py = -1;
	while (py < mm_h + 1)
	{
		px = -1;
		while (px < mm_w + 1)
		{
			x = mm->margin + px;
			if (px == -1 || px == mm_w || py == -1 || py == mm_h)
				draw_pixel(mm->game, x, mm->margin + py, COLOR_BORDER);
			else
				draw_pixel(mm->game, x, mm->margin + py, COLOR_BG);
			px++;
		}
		py++;
	}
}

void	render_minimap(t_game *game)
{
	t_minimap	mm;

	if (!game || !game->map)
		return ;
	mm.game = game;
	mm.cell = MINIMAP_SCALE;
	mm.margin = MINIMAP_MARGIN;
	calc_map_size(game->map, &mm.width, &mm.height);
	draw_minimap_background(&mm);
	draw_minimap_cells(&mm);
	draw_player_minimap(&mm);
}
