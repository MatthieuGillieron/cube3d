/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_valid_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:27:39 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/04 11:45:57 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

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

static int	validate_map_content(char *line, int y, \
	int len_line, t_validation_ctx *ctx)
{
	int	j;

	j = 0;
	while (j < len_line)
	{
		if (!is_playable(line[j]) && (line[j] != '1' && line[j] != '\n'))
		{
			printf("Error\nUnknown map symbol: %c at line %d, col %d\n",
				line[j], y + 1, j + 1);
			return (0);
		}
		if (is_player(line[j]))
		{
			ctx->info->player_count++;
			ctx->info->player->x = j;
			ctx->info->player->y = y;
			ctx->info->player->direction = line[j];
		}
		if (!is_valid_surrounding(ctx->map, y, j))
			return (0);
		j++;
	}
	return (1);
}

static int	validate_line_end(char *line, int len_line, int last_index)
{
	if (last_index >= 0)
	{
		if (last_index + 1 >= len_line || line[last_index + 1] != '1')
			return (0);
	}
	return (1);
}

static int	check_map_line(char *line, int y, char **map, t_map_check *info)
{
	int					len_line;
	int					last_index;
	t_validation_ctx	ctx;

	ctx.map = map;
	ctx.info = info;
	len_line = check_line(line, &last_index);
	if (!validate_map_content(line, y, len_line, &ctx))
		return (0);
	if (!validate_line_end(line, len_line, last_index))
		return (0);
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
