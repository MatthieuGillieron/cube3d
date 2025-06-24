/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_split_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 08:41:16 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/24 08:43:22 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	find_map_start(char **lines, int i)
{
	int	j;

	while (lines[i] != NULL)
	{
		j = 0;
		while (lines[i][j] == ' ' || lines[i][j] == '\t')
			j++;
		if (lines[i][j] == '1' || lines[i][j] == '0')
			return (i);
		i++;
	}
	return (-1);
}

int	is_data_complete(t_map_data *data)
{
	return (data->textures.no && data->textures.so && \
		data->textures.we && data->textures.ea && \
		data->colors.floor && data->colors.ceiling && \
		data->map && data->map[0]);
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
			return (0);
		j++;
	}
	data->map[j] = NULL;
	return (1);
}
