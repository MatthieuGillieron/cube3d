/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:32:34 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/23 17:54:05 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <stdio.h> 

typedef struct s_texture {
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_texture;

typedef struct s_color {
	char	*floor;
	char	*ceiling;
}	t_color;

typedef struct s_map_data {
	t_texture	textures;
	t_color		colors;
	char		**map;
}	t_map_data;

typedef struct s_player
{
    int		x;
    int		y;
    char	direction;
}   t_player;

//--------------split_map.c-----------------------
char	**open_map(char *map);
int		split_sections(char **lines, t_map_data *data);
//--------------assign_map.c------------------------
int		find_map_start(char **lines, int i);
void	assign_texture_or_color(char *line, t_map_data *data, int *found);
//---------------free.c------------------------
void	free_map_data(t_map_data *data);
//--------------is_map_ok.c--------------------
int		is_map_enclosed(char **map, t_player *player);

#endif