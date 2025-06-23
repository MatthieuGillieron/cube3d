/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:32:34 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/23 18:30:51 by mg               ###   ########.fr       */
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

typedef struct s_colors_int
{
	int	floor;
	int	ceiling;
	int	floor_set;
	int	ceiling_set;
}	t_colors_int;

typedef struct s_map_data {
	t_texture textures;
	//t_color colors;
	t_colors_int colors_int;
	char **map;
}	t_map_data;

int		find_map_start(char **lines, int i);
void	assign_texture_or_color(char *line, t_map_data *data, int *found);
void	free_map_data(t_map_data *data);