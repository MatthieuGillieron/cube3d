/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:58:45 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/29 17:39:45 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <stdio.h> 
# include <math.h>
# include "../mlx/mlx.h"

# define FOV 1.0472
//--------[ STRUCTURE ]----------
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
	double	x;
	double	y;
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
	int		width;
	int		height;
}	t_img;

typedef struct s_textures
{
	t_img	north;
	t_img	south;
	t_img	east;
	t_img	west;
}	t_textures;

typedef struct s_key_state {
	int forward;
	int backward;
	int left;
	int right;
	int rotate_left;
	int rotate_right;
} t_key_state;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	int			win_w;
	int			win_h;
	t_map_data	map_data;
	t_color		color;
	t_player	player;
	char		**map;
	t_textures	textures;
	t_key_state keys;
}	t_game;

typedef struct s_ray_pos
{
	double	pos_x;
	double	pos_y;
	int		map_x;
	int		map_y;
}	t_ray_pos;

typedef struct s_ray_hit
{
	double	distance;
	int		map_x;
	int		map_y;
	int		side;
	double	wall_x;
}	t_ray_hit;

typedef struct s_ray_dir
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
}	t_ray_dir;

typedef struct s_draw_params {
	int		x;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	int		line_height;
}	t_draw_params;

//-----------[ PROTOTYPES ]----------------

//-----------*** events ***----------------
int			close_window(t_game *game);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
void		update_movement(t_game *game);

//-----------*** init ***------------------
int			init_game(t_game *game);
int			load_textures(t_game *game);

//-----------*** movement ***--------------
void		move_forward(t_game *game);
void		move_backward(t_game *game);
void		move_left(t_game *game);
void		move_right(t_game *game);
void		rotate_player(t_game *game, int direction);

//-----------*** parsing ***---------------
char		**open_map(char *map);
int			split_sections(char **lines, t_map_data *data);
int			find_map_start(char **lines, int i);
int			copy_map(char **lines, t_map_data *data, int start);
int			is_data_complete(t_map_data *data);
int			find_map_start(char **lines, int i);
int			assign_texture_or_color(char *line, t_map_data *data, int *found);
int			is_map_enclosed(char **map, t_player *player);
int			is_player(char c);
int			is_playable(char c);
int			check_file(char **files, t_map_data *map);
int			rgb_to_hex(char *rgb_str);
void		parse_colors(t_map_data *data);
int			is_line_empty(const char *line);

//-----------*** raycasting ***------------
t_ray_hit	cast_ray(t_game *game, double ray_angle);

//-----------*** render ***----------------
int			render_loop(void *param);
void		render_background(t_game *game);
void		draw_wall_slice(t_game *game, int x, \
	t_ray_hit *hit, double ray_angle);
t_img		*get_wall_texture(t_game *game, \
	t_ray_hit *hit, double ray_angle);
int			get_texture_color(t_img *texture, int x, int y);

//-----------*** utils ***-----------------
void		free_map_data(t_map_data *data);
void		assign_direction(t_player *player);

//------------*** TEST ***-----------------
void		print_map_data(t_map_data *data);
void		print_player(t_player *player);
void		print_map(char **map);
void		print_color(t_color *col);
void		print_texture(t_texture *tex);

#endif