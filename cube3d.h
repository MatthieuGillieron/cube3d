/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:32:34 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/23 17:07:57 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
# include "libft/libft.h"
#include <stdio.h> 

typedef struct s_texture {
	char *no;
	char *so;
	char *we;
	char *ea;
}	t_texture;

typedef struct s_color {
	char *floor;
	char *ceiling;
}	t_color;

typedef struct s_map_data {
	t_texture textures;
	t_color colors;
	char **map;
}	t_map_data;

int		find_map_start(char **lines, int i);
void	assign_texture_or_color(char *line, t_map_data *data, int *found);
void	free_map_data(t_map_data *data);