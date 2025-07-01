/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_map_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:01:20 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/01 11:37:36 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	calc_map_size(char **map, int *width, int *height)
{
	int	i;
	int	w;
	int	last_nonspace;

	*width = 0;
	*height = 0;
	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		w = 0;
		last_nonspace = -1;
		while (map[i][w])
		{
			if (map[i][w] != ' ' && map[i][w] != '\n')
				last_nonspace = w;
			w++;
		}
		if (last_nonspace + 1 > *width)
			*width = last_nonspace + 1;
		i++;
	}
	*height = i;
}
