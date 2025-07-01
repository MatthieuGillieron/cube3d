/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:23:26 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/24 20:20:16 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	check_extra_lines_after_map(char **lines, int map_start, t_map_data *data)
{
	int	map_lines_count;
	int	i;
	int	j;

	map_lines_count = 0;
	while (data->map[map_lines_count] != NULL)
		map_lines_count++;
	i = map_start + map_lines_count;
	while (lines[i] != NULL)
	{
		j = 0;
		while (lines[i][j] == ' ' || lines[i][j] == '\t')
			j++;
		if (lines[i][j] != '\0' && lines[i][j] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static int	check_header_lines(char **lines, t_map_data *data, int *index)
{
	int	found;
	int	i;

	found = 0;
	i = 0;
	while (lines[i] != NULL && found < 6)
	{
		if (is_line_empty(lines[i]))
		{
			i++;
			continue ;
		}
		if (!assign_texture_or_color(lines[i], data, &found))
			return (-1);
		i++;
	}
	*index = i;
	return (found == 6);
}

static int	check_blank_lines_between(char **lines, int start, int end)
{
	int	j;

	j = start;
	while (j < end)
	{
		if (!is_line_empty(lines[j]))
			return (0);
		j++;
	}
	return (1);
}

int	split_sections(char **lines, t_map_data *data)
{
	int	i;
	int	map_start;

	i = 0;
	if (check_header_lines(lines, data, &i) == -1)
		return (0);
	map_start = find_map_start(lines, i);
	if (map_start < 0)
		return (0);
	if (!check_blank_lines_between(lines, i, map_start))
		return (0);
	if (!copy_map(lines, data, map_start))
		return (0);
	if (!is_data_complete(data))
		return (0);
	if (!check_extra_lines_after_map(lines, map_start, data))
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
	line = malloc(sizeof(char *) * 256);
	if (!line)
		return (NULL);
	current = get_next_line(fd);
	i = 0;
	while (current != NULL && i < 256)
	{
		line[i] = current;
		i++;
		current = get_next_line(fd);
	}
	line[i] = NULL;
	close(fd);
	return (line);
}
