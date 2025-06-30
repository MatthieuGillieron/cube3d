/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_minimap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:49:23 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/30 10:00:37 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	draw_minimap_cell(t_minimap *mm, int map_x, int map_y, \
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

static void	draw_minimap_cells(t_minimap *mm)
{
	int				map_y;
	int				map_x;
	unsigned int	color;

	map_y = 0;
	while (mm->game->map[map_y])
	{
		map_x = 0;
		while (mm->game->map[map_y][map_x])
		{
			if (mm->game->map[map_y][map_x] == '1')
				color = COLOR_WALL;
			else
				color = COLOR_EMPTY;
			draw_minimap_cell(mm, map_x, map_y, color);
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
	py = -2;
	while (py < mm_h + 2)
	{
		px = -2;
		while (px < mm_w + 2)
		{
			x = mm->margin + px;
			if (px == -2 || px == mm_w + 1 || py == -2 || py == mm_h + 1)
				draw_pixel(mm->game, x, mm->margin + py, COLOR_BORDER);
			else if (px == -1 || px == mm_w || py == -1 || py == mm_h)
				draw_pixel(mm->game, x, mm->margin + py, COLOR_BORDER);
			else
				draw_pixel(mm->game, x, mm->margin + py, COLOR_BG);
			px++;
		}
		py++;
	}
}

static void	calc_map_size(char **map, int *width, int *height)
{
	int	i;
	int	w;

	*width = 0;
	*height = 0;
	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		w = 0;
		while (map[i][w])
			w++;
		if (w > *width)
			*width = w;
		i++;
	}
	*height = i;
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
