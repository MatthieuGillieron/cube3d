/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:58:45 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/01 11:00:18 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <stdio.h> 
# include <math.h>
# include <float.h>
# include "../mlx/mlx.h"

# define FOV 1.0472
# define MOVE_SPEED 0.03
# define ROTATE_SPEED 0.025
# define MOUSE_SENS 0.003
# define MINIMAP_SCALE 5
# define MINIMAP_MARGIN 16
# define COLOR_WALL 0x444444
# define COLOR_EMPTY 0xEEEEEE
# define COLOR_BG 0x22222288
# define COLOR_BORDER 0x888888
# define COLOR_PLAYER 0x00CC66
# define COLOR_DIR 0x0077FF
# define PLAYER_RADIUS 0.2

# ifdef __linux__
#  define KEY_W 119
#  define KEY_S 115
#  define KEY_A 97
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_ESC 65307
# else
#  define KEY_W 13
#  define KEY_S 1
#  define KEY_A 0
#  define KEY_D 2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_ESC 53
# endif

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
	int	forward;
	int	backward;
	int	left;
	int	right;
	int	rotate_left;
	int	rotate_right;
}	t_key_state;

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
	t_key_state	keys;
	int			collision_active;
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
typedef struct s_line_params
{
	t_game			*game;
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	unsigned int	color;
}	t_line_params;

typedef struct s_minimap
{
	t_game	*game;
	int		width;
	int		height;
	int		cell;
	int		margin;
}	t_minimap;

typedef struct s_circle_params
{
	t_game			*game;
	int				cx;
	int				cy;
	int				r;
	unsigned int	color;
}	t_circle_params;

typedef struct s_bounds
{
	int	min_x;
	int	max_x;
	int	min_y;
	int	max_y;
}	t_bounds;

typedef struct s_walkable
{
	char		**map;
	double		cx;
	double		cy;
	double		best_dist;
	double		best_x;
	double		best_y;
	int			found;
}	t_walkable;

//-----------[ PROTOTYPES ]----------------

//-----------*** events ***----------------
int			close_window(t_game *game);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
void		update_movement(t_game *game);
int			mouse_motion(int x, int y, t_game *game);

//-----------*** init ***------------------
int			init_game(t_game *game);
int			load_textures(t_game *game);

//-----------*** movement ***--------------
void		move_forward(t_game *game);
void		move_backward(t_game *game);
//void		move_left(t_game *game);
//void		move_right(t_game *game);
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
void		render_minimap(t_game *game);

//-----------*** utils ***-----------------
void		free_map_data(t_map_data *data);
void		assign_direction(t_player *player);
void		draw_player_minimap(t_minimap *mm);
void		draw_line(t_line_params *line);
int			get_direction(int start, int end);
void		draw_circle(t_circle_params *circle);
void		draw_pixel(t_game *game, int x, int y, unsigned int color);
void		update_best_position(t_walkable *w, double r);
int			is_walkable(char **map, double x, double y);
int			check_area(char **map, t_bounds b);
int			cell_is_walkable(char **map, int x, int y);
void		calc_map_size(char **map, int *width, int *height);

//------------*** TEST ***-----------------
void		print_map_data(t_map_data *data);
void		print_player(t_player *player);
void		print_map(char **map);
void		print_color(t_color *col);
void		print_texture(t_texture *tex);

#endif