/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 08:41:16 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/02 09:08:27 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	is_line_potential_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (line[i] == '1' || line[i] == '0');
}

int	is_line_empty(const char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

int	find_map_start(char **lines, int i)
{
	while (lines[i])
	{
		if (is_line_empty(lines[i]))
		{
			i++;
			continue ;
		}
		if (is_line_potential_map(lines[i]))
			return (i);
		return (-1);
	}
	return (-1);
}

int	is_data_complete(t_map_data *data)
{
	return (data->textures.no && data->textures.so
		&& data->textures.we && data->textures.ea
		&& data->colors.floor && data->colors.ceiling
		&& data->map && data->map[0]);
}

int	copy_map(char **lines, t_map_data *data, int start)
{
	int	count;
	int	j;

	count = 0;
	j = 0;
	while (lines[start + count] != NULL)
		count++;
	data->map = malloc(sizeof(char *) * (count + 1));
	if (!data->map)
		return (0);
	while (j < count)
	{
		data->map[j] = ft_strdup(lines[start + j]);
		if (!data->map[j])
		{
			while (--j >= 0)
				free(data->map[j]);
			free(data->map);
			data->map = NULL;
			return (0);
		}
		j++;
	}
	data->map[j] = NULL;
	return (1);
}
