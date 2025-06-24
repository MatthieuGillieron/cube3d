/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:58:45 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/24 11:13:02 by maximemarti      ###   ########.fr       */
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
	int		set_floor;
	int		set_ceiling;
}	t_color;

typedef struct s_player
{
	int		x;
	int		y;
	char	direction;
	double	angle;
}	t_player;

typedef struct s_map_data {
	t_texture	textures;
	t_color		colors;
	t_player	player;
	char		**map;
}	t_map_data;

typedef struct s_map_check
{
	t_player	*player;
	int			player_count;
}	t_map_check;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	int			win_w;
	int			win_h;
	t_map_data	map_data;
}	t_game;

//--------------parsing----------------
//--------------p_split_map.c-----------------------
char	**open_map(char *map);
int		split_sections(char **lines, t_map_data *data);
//------------p_split_map_utils.c----------------
int		find_map_start(char **lines, int i);
int		copy_map(char **lines, t_map_data *data, int start);
int		is_data_complete(t_map_data *data);
//--------------p_assign_map.c------------------------
int		find_map_start(char **lines, int i);
int		assign_texture_or_color(char *line, t_map_data *data, int *found);
//--------------p_map_ok.c--------------------
int		is_map_enclosed(char **map, t_player *player);
//-------------p_map_ok_u.c--------------
int		is_player(char c);
int		is_playable(char c);
//-------------check_texture.c--------------
int		check_file(char **files, t_map_data	map);
//---------------utils------------------------
//---------------u_free.c------------------------
void	free_map_data(t_map_data *data);
void	assign_direction(t_player *player);
//-------------------print-helper.c----------------
void	print_map_data(t_map_data *data);
void	print_player(t_player *player);
void	print_map(char **map);
void	print_color(t_color *col);
void	print_texture(t_texture *tex);
//-------------------color.c----------------
int		rgb_to_hex(char *rgb_str);
void	parse_colors(t_map_data *data);
#endif