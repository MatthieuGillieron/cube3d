/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 00:00:00 by mg                #+#    #+#             */
/*   Updated: 2025/01/02 00:00:00 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define FOV 60
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_texture
{
	char	*path;
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_textures
{
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
}	t_textures;

typedef struct s_colors
{
	int	floor;
	int	ceiling;
}	t_colors;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}	t_player;

typedef struct s_ray
{
	t_vector	dir;
	t_vector	delta_dist;
	t_vector	side_dist;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
}	t_ray;

typedef struct s_wall
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_wall;

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
	char		**map;
	int			map_width;
	int			map_height;
	t_player	player;
	t_textures	textures;
	t_colors	colors;
}	t_game;

/* Init functions */
int		init_game(t_game *game);
int		init_player(t_game *game, char **map);
int		init_mlx(t_game *game);
int		init_textures(t_game *game, char **texture_paths);

/* Parsing functions */
int		parse_file(char *filename, t_game *game);
int		parse_textures(char *line, char **texture_paths);
int		parse_colors(char *line, t_colors *colors);
int		parse_map(char **lines, t_game *game);
int		validate_map(char **map, t_player *player);

/* Raycasting functions */
void	raycast(t_game *game);
void	init_ray(t_ray *ray, t_player *player, int x);
void	perform_dda(t_ray *ray, char **map);
void	calculate_wall(t_ray *ray, t_wall *wall);

/* Render functions */
void	render_frame(t_game *game);
void	draw_wall(t_game *game, int x, t_wall *wall, t_texture *tex);
void	draw_floor_ceiling(t_game *game);

/* Event functions */
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		close_window(t_game *game);

/* Movement functions */
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
int		check_collision(t_game *game, double new_x, double new_y);

/* Utils functions */
void	cleanup_game(t_game *game);
void	error_exit(char *message);
double	deg_to_rad(double degrees);
int		rgb_to_int(int r, int g, int b);
char	*trim_whitespace(char *str);

#endif