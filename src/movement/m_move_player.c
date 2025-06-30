/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_move_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:57:11 by mg                #+#    #+#             */
/*   Updated: 2025/06/30 10:17:32 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	cell_is_walkable(char **map, int x, int y)
{
	int	map_h;
	int	map_w;

	map_h = 0;
	map_w = 0;
	if (y < 0)
		return (0);
	while (map[map_h])
		map_h++;
	if (y >= map_h)
		return (0);
	while (map[y][map_w])
		map_w++;
	if (x < 0 || x >= map_w)
		return (0);
	if (map[y][x] == '1')
		return (0);
	return (1);
}

static int	check_area(char **map, t_bounds b)
{
	int	i;
	int	j;

	i = b.min_y;
	while (i <= b.max_y)
	{
		j = b.min_x;
		while (j <= b.max_x)
		{
			if (!cell_is_walkable(map, j, i))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	is_walkable(char **map, double x, double y)
{
	t_bounds	b;

	b.min_x = (int)(x - PLAYER_RADIUS);
	b.max_x = (int)(x + PLAYER_RADIUS);
	b.min_y = (int)(y - PLAYER_RADIUS);
	b.max_y = (int)(y + PLAYER_RADIUS);
	return (check_area(map, b));
}

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + cos(game->player.angle) * MOVE_SPEED;
	new_y = game->player.y + sin(game->player.angle) * MOVE_SPEED;
	if (is_walkable(game->map, new_x, game->player.y))
		game->player.x = new_x;
	if (is_walkable(game->map, game->player.x, new_y))
		game->player.y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - cos(game->player.angle) * MOVE_SPEED;
	new_y = game->player.y - sin(game->player.angle) * MOVE_SPEED;
	if (is_walkable(game->map, new_x, game->player.y))
		game->player.x = new_x;
	if (is_walkable(game->map, game->player.x, new_y))
		game->player.y = new_y;
}
/*
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + cos(game->player.angle - M_PI / 2) * MOVE_SPEED;
	new_y = game->player.y + sin(game->player.angle - M_PI / 2) * MOVE_SPEED;
	if (game->map[(int)new_y][(int)new_x] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + cos(game->player.angle + M_PI / 2) * MOVE_SPEED;
	new_y = game->player.y + sin(game->player.angle + M_PI / 2) * MOVE_SPEED;
	if (game->map[(int)new_y][(int)new_x] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}*/
