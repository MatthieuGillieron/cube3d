/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_ok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:27:39 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/23 17:57:16 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_playable(char c)
{
	return (c == '0' || is_player(c));
}

int	is_valid_surrounding(char **map, int y, int x)
{
	if (!is_playable(map[y][x]))
		return (1);
	if (y == 0 || x == 0 || !map[y + 1][x] || !map[y][x + 1])
		return (0);
	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' ||
		map[y][x - 1] == ' ' || map[y][x + 1] == ' ' ||
		map[y - 1][x] == '\0' || map[y + 1][x] == '\0' ||
		map[y][x - 1] == '\0' || map[y][x + 1] == '\0')
		return (0);
	return (1);
}

int	is_map_enclosed(char **map, t_player *player)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player(map[i][j]))
			{
				player_count++;
				player->x = j;
				player->y = i;
				player->direction = map[i][j];
			}
			if (!is_valid_surrounding(map, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (player_count == 1);
}
