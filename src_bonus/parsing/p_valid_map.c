/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map_ok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:27:39 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/24 09:58:07 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	is_valid_surrounding(char **map, int y, int x)
{
	int	len_up;
	int	len_down;
	int	len_curr;

	if (!is_playable(map[y][x]))
		return (1);
	if (y == 0 || x == 0)
		return (0);
	if (!map[y - 1] || !map[y + 1])
		return (0);
	len_curr = ft_strlen(map[y]);
	len_up = ft_strlen(map[y - 1]);
	len_down = ft_strlen(map[y + 1]);
	if (x >= len_curr || x >= len_up || x >= len_down)
		return (0);
	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' ||
		map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
		return (0);
	return (1);
}

static int	check_line(char *line, int *last_playable)
{
	int	i;

	i = 0;
	*last_playable = -1;
	while (line[i])
	{
		if (is_playable(line[i]))
			*last_playable = i;
		i++;
	}
	return (i);
}

static int	check_map_line(char *line, int y, char **map, t_map_check *info)
{
	int	j;
	int	len_line;
	int	last_index;

	len_line = check_line(line, &last_index);
	j = 0;
	while (j < len_line)
	{
		if (is_player(line[j]))
		{
			info->player_count++;
			info->player->x = j;
			info->player->y = y;
			info->player->direction = line[j];
		}
		if (!is_valid_surrounding(map, y, j))
			return (0);
		j++;
	}
	if (last_index >= 0)
	{
		if (last_index + 1 >= len_line || line[last_index + 1] != '1')
			return (0);
	}
	return (1);
}

int	is_map_enclosed(char **map, t_player *player)
{
	int			i;
	t_map_check	info;

	i = 0;
	info.player = player;
	info.player_count = 0;
	while (map[i])
	{
		if (!check_map_line(map[i], i, map, &info))
			return (0);
		i++;
	}
	return (info.player_count == 1);
}
