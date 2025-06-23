/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:15:08 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/23 18:59:31 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	main(int ac, char **av)
{
	char		**lines;
	t_map_data	map = {0};
	t_player	player;

	if (ac != 2)
		return (1);
	lines = open_map(av[1]);
	if (!split_sections(lines, &map))
	{
		printf("Error\nInvalid map format.\n");
		free_map_data(&map);
		free(lines);
		return (1);
	}
	if (!is_map_enclosed(map.map, &player))
		printf("Map not good\n");
	else
		printf("Player position: x=%d, y=%d, direction=%c\n", player.x, player.y, player.direction);
}
