/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_colors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:53:32 by mg                #+#    #+#             */
/*   Updated: 2025/06/23 18:40:26 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

static char	*skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

static int	parse_component(char **line)
{
	int	value;

	value = 0;
	*line = skip_spaces(*line);
	if (!ft_isdigit(**line))
		return (-1);
	while (ft_isdigit(**line))
	{
		value = value * 10 + (**line - '0');
    	(*line)++;
	}
	if (value < 0 || value > 255)
		return (-1);
	return (value);
}

int	extract_rgb(char *pos, int *r, int *g, int *b)
{
	*r = parse_component(&pos);
	if (*r == -1)
		return (1);
	if (*pos != ',')
		return (1);
	pos++;
	*g = parse_component(&pos);
	if (*g == -1)
		return (1);
	if (*pos != ',')
		return (1);
	pos++;
	*b = parse_component(&pos);
	if (*b == -1)
		return (1);
	pos = skip_spaces(pos);
	if (*pos != '\0')
		return (1);
	return (0);
}

void	set_color_value(t_map_data *data, int color, int is_floor)
{
	if (is_floor)
	{
		data->colors_int.floor = color;
		data->colors_int.floor_set = 1;
	}
	else
	{
		data->colors_int.ceiling = color;
		data->colors_int.ceiling_set = 1;
	}
}

int	parse_color(char *line, t_map_data *data, int is_floor)
{
	int		r;
	int		g;
	int		b;
	int		color;
	char	*pos;

	pos = line + 1;
	pos = skip_spaces(pos);
	if (extract_rgb(pos, &r, &g, &b) != 0)
		return (1);
	color = (r << 16) | (g << 8) | b;
	set_color_value(data, color, is_floor);
	return (0);
}
