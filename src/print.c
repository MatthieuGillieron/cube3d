/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 08:44:03 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/29 15:14:56 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	print_texture(t_texture *tex)
{
	printf("Textures:\n");
	printf("  NO: %s\n", tex->no);
	printf("  SO: %s\n", tex->so);
	printf("  WE: %s\n", tex->we);
	printf("  EA: %s\n", tex->ea);
}

void	print_color(t_color *col)
{
	printf("Colors:\n");
	printf("  Floor: %s\n", col->floor);
	printf("  Ceiling: %s\n", col->ceiling);
	printf("  Floor hex: %X\n", col->set_floor);
	printf("  Ceiling hex: %X\n", col->set_ceiling);
}

void	print_map(char **map)
{
	printf("Map:\n");
	if (!map)
	{
		printf("  (null)\n");
		return ;
	}
	for (int i = 0; map[i]; i++)
	{
		printf("  %s\n", map[i]);
	}
}

void	print_map_data(t_map_data *data)
{
	printf("=== Map Data ===\n");
	print_texture(&data->textures);
	print_color(&data->colors);
	print_map(data->map);
}

void	print_player(t_player *player)
{
	printf("Player:\n");
	printf("  X: %f\n", player->x);
	printf("  Y: %f\n", player->y);
	printf("  Direction: %c\n", player->direction);
	printf("  Direction angle : %f\n", player->angle);
}
