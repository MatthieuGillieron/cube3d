/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_cleanup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:07:01 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/04 12:13:05 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

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

void	free_map_data(t_map_data *data)
{
	int	i;

	i = 0;
	free(data->textures.no);
	free(data->textures.so);
	free(data->textures.we);
	free(data->textures.ea);
	free(data->colors.floor);
	free(data->colors.ceiling);
	if (data->map)
	{
		while (data->map[i])
			free(data->map[i++]);
		free(data->map);
	}
}
