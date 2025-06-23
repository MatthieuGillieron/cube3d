/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_check_file_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:42:31 by mg                #+#    #+#             */
/*   Updated: 2025/06/23 17:04:11 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_config
{
	char	*texture_no;
	char	*texture_so;
	char	*texture_we;
	char	*texture_ea;

}	t_config;

static char	*skip_space(char *line)
{
	while (*line)
	{
		if (*line == ' ' || *line == '\t')
			line++;
	}
	return (line);
}

int	parse_texture_path(char *line, t_texture *cfg)
{
	line = skip_space(line);

	if (!ft_strncmp(line, "NO ", 3))
	{
		if (cfg->no)
			return 1;
		cfg->no = strdup(skip_spaces(line + 3));
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		if (cfg->so)
			return 1;
		cfg->so = strdup(skip_spaces(line + 3));
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		if (cfg->we)
			return 1;
		cfg->we = strdup(skip_spaces(line + 3));
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		if (cfg->ea)
			return 1;
		cfg->ea = strdup(skip_spaces(line + 3));
	}
}
