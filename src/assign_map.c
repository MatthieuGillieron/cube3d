/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:55:25 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/23 17:03:48 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	assign_north_south(char *line, t_map_data *data, int *found)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && !data->textures.no)
	{
		data->textures.no = ft_strdup(line + 3);
		(*found)++;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0 && !data->textures.so)
	{
		data->textures.so = ft_strdup(line + 3);
		(*found)++;
	}
}

static void	assign_west_east(char *line, t_map_data *data, int *found)
{
	if (ft_strncmp(line, "WE ", 3) == 0 && !data->textures.we)
	{
		data->textures.we = ft_strdup(line + 3);
		(*found)++;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0 && !data->textures.ea)
	{
		data->textures.ea = ft_strdup(line + 3);
		(*found)++;
	}
}

static void	assign_floor_ceiling(char *line, t_map_data *data, int *found)
{
	if (ft_strncmp(line, "F ", 2) == 0 && !data->colors.floor)
	{
		data->colors.floor = ft_strdup(line + 2);
		(*found)++;
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && !data->colors.ceiling)
	{
		data->colors.ceiling = ft_strdup(line + 2);
		(*found)++;
	}
}

void	assign_texture_or_color(char *line, t_map_data *data, int *found)
{
	assign_north_south(line, data, found);
	assign_west_east(line, data, found);
	assign_floor_ceiling(line, data, found);
}

int	find_map_start(char **lines, int i)
{
	while (lines[i] && ft_strlen(lines[i]) == 1)
		i++;
	return (i);
}
