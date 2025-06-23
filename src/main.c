/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:15:08 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/23 17:10:10 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	is_data_complete(t_map_data *data)
{
	return (
		data->textures.no && data->textures.so && \
		data->textures.we && data->textures.ea && \
		data->colors.floor && data->colors.ceiling && \
		data->map && data->map[0]
	);
}

int	copy_map(char **lines, t_map_data *data, int start)
{
	int	count;
	int	j;

	count = 0;
	j = 0;
	while (lines[start + count])
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

int	split_sections(char **lines, t_map_data *data)
{
	int	i;
	int	found;
	int	map_start;

	i = 0;
	found = 0;
	while (lines[i] && found < 6)
	{
		assign_texture_or_color(lines[i], data, &found);
		i++;
	}
	map_start = find_map_start(lines, i);
	if (!copy_map(lines, data, map_start))
		return (0);
	if (!is_data_complete(data))
		return (0);
	return (1);
}

char	**open_map(char *map)
{
	int		fd;
	char	**line;
	char	*current;
	int		i;

	if (!map)
		return (NULL);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = malloc((sizeof(char *) * 256));
	if (!line)
		return (NULL);
	current = get_next_line(fd);
	i = 0;
	while (current && i < 256)
	{
		line[i++] = current;
		current = get_next_line(fd);
	}
	line[i] = NULL;
	close(fd);
	return (line);
}

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
