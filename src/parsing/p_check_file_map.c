/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_check_file_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:42:31 by mg                #+#    #+#             */
/*   Updated: 2025/06/23 18:36:24 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../cube3d.h"

static char	*skip_space(char *str)
{
	while (*str)
	{
		if (*str == ' ' || *str == '\t')
			str++;
	}
	return (str);
}

int	parse_texture_path(char *line, t_texture *texture)
{
	line = skip_space(line);

	if (!ft_strncmp(line, "NO ", 3))
	{
		if (texture->no)
			return (1);
		texture->no = strdup(skip_spaces(line + 3));
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		if (texture->so)
			return (1);
		texture->so = strdup(skip_spaces(line + 3));
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		if (texture->we)
			return (1);
		texture->we = strdup(skip_spaces(line + 3));
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		if (texture->ea)
			return (1);
		texture->ea = strdup(skip_spaces(line + 3));
	}
}
