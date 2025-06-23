/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:15:08 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/23 17:23:43 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	main(int ac, char **av)
{
	char		**lines;
	t_map_data	map = {0};

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
	printf("NO: %s", map.textures.no);
	printf("SO: %s", map.textures.so);
	printf("WE: %s", map.textures.we);
	printf("EA: %s", map.textures.ea);
	printf("F: %s", map.colors.floor);
	printf("C: %s", map.colors.ceiling);
	for (int i = 0; map.map[i]; i++)
		printf("MAP: %s", map.map[i]);
}
