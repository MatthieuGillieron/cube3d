/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:58:45 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/24 00:19:48 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <stdio.h> 
# include "../mlx/mlx.h"

typedef struct s_texture {
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_texture;

typedef struct s_color {
	char	*floor;
	char	*ceiling;
	int		set_flor;
	int		set_ceiling;
}	t_color;

typedef struct s_player
{
	int		x;
	int		y;
	char	direction;
}	t_player;

typedef struct s_map_data {
	t_texture textures;
	t_color colors;
	t_player player;
	char **map;
}	t_map_data;


//--------------split_map.c-----------------------
char	**open_map(char *map);
int		split_sections(char **lines, t_map_data *data);
//--------------assign_map.c------------------------
int		find_map_start(char **lines, int i);
int		assign_texture_or_color(char *line, t_map_data *data, int *found);
//---------------free.c------------------------
void	free_map_data(t_map_data *data);
//--------------is_map_ok.c--------------------
int		is_map_enclosed(char **map, t_player *player);
int		parse_color(t_map_data *data, int is_floor);
#endif