/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:15:08 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/24 10:45:54 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	main(int ac, char **av)
{
	char		**files;
	t_map_data	map = {0};

	if (ac != 2)
		return (1);
	files = open_map(av[1]);
	if (!check_file(files, map))
		return (1);
	return (0);
}
