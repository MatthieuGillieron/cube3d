/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:15:08 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/24 23:21:54 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	init_ray_vars(t_game *game, double ray_angle,
	t_ray_pos *pos, t_ray_dir *dir)
{
	pos->pos_x = (double)game->player.x + 0.5;
	pos->pos_y = (double)game->player.y + 0.5;
	pos->map_x = (int)pos->pos_x;
	pos->map_y = (int)pos->pos_y;
	dir->ray_dir_x = cos(ray_angle);
	dir->ray_dir_y = sin(ray_angle);
	dir->delta_dist_x = (dir->ray_dir_x == 0) ? 1e30 : fabs(1 / dir->ray_dir_x);
	dir->delta_dist_y = (dir->ray_dir_y == 0) ? 1e30 : fabs(1 / dir->ray_dir_y);
	if (dir->ray_dir_x < 0)
	{
		dir->step_x = -1;
		dir->side_dist_x = (pos->pos_x - pos->map_x) * dir->delta_dist_x;
	}
	else
	{
		dir->step_x = 1;
		dir->side_dist_x = (pos->map_x + 1.0 - pos->pos_x) * dir->delta_dist_x;
	}
	if (dir->ray_dir_y < 0)
	{
		dir->step_y = -1;
		dir->side_dist_y = (pos->pos_y - pos->map_y) * dir->delta_dist_y;
	}
	else
	{
		dir->step_y = 1;
		dir->side_dist_y = (pos->map_y + 1.0 - pos->pos_y) * dir->delta_dist_y;
	}
}

static int	perform_dda(t_game *game, t_ray_pos *pos, t_ray_dir *dir, int *side)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (dir->side_dist_x < dir->side_dist_y)
		{
			dir->side_dist_x += dir->delta_dist_x;
			pos->map_x += dir->step_x;
			*side = 0;
		}
		else
		{
			dir->side_dist_y += dir->delta_dist_y;
			pos->map_y += dir->step_y;
			*side = 1;
		}
		if (game->map[pos->map_y] && game->map[pos->map_y][pos->map_x] == '1')
			hit = 1;
	}
	return (hit);
}

t_ray_hit	cast_ray(t_game *game, double ray_angle)
{
	t_ray_hit	hit;
	t_ray_pos	pos;
	t_ray_dir	dir;
	int			side;

	init_ray_vars(game, ray_angle, &pos, &dir);
	perform_dda(game, &pos, &dir, &side);
	if (side == 0)
		hit.distance = (pos.map_x - pos.pos_x + (1 - dir.step_x) / 2) / dir.ray_dir_x;
	else
		hit.distance = (pos.map_y - pos.pos_y + (1 - dir.step_y) / 2) / dir.ray_dir_y;
	if (side == 0)
		hit.wall_x = pos.pos_y + hit.distance * dir.ray_dir_y;
	else
		hit.wall_x = pos.pos_x + hit.distance * dir.ray_dir_x;
	hit.wall_x -= floor(hit.wall_x);
	hit.map_x = pos.map_x;
	hit.map_y = pos.map_y;
	hit.side = side;
	return (hit);
}

void	render_background(t_game *game)
{
	int		x;
	int		y;
	int		color;
	char	*dst;

	y = 0;
	while (y < game->win_h)
	{
		x = 0;
		while (x < game->win_w)
		{
			if (y < game->win_h / 2)
				color = game->color.set_ceiling;
			else
				color = game->color.set_floor;
			dst = game->img.addr
				+ (y * game->img.line_len + x * (game->img.bpp / 8));
			*(unsigned int *)dst = color;
			x++;
		}
		y++;
	}
}
void	draw_wall_slice(t_game *game, int x, t_ray_hit *hit)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		y;
	char	*dst;
	int		color;

	if (hit->distance <= 0)
		hit->distance = 0.1;

	line_height = (int)(game->win_h / hit->distance);

	draw_start = -line_height / 2 + game->win_h / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + game->win_h / 2;
	if (draw_end >= game->win_h)
		draw_end = game->win_h - 1;

	// Simulate light shading depending on side
	if (hit->side == 0)
		color = 0xFFFFFF; // bright
	else
		color = 0xAAAAAA; // dimmer

	y = draw_start;
	while (y <= draw_end)
	{
		dst = game->img.addr + (y * game->img.line_len + x * (game->img.bpp / 8));
		*(unsigned int *)dst = color;
		y++;
	}
}

int	render_loop(void *param)
{
	t_game		*game;
	int			x;
	double		ray_angle;
	double		fov;
	double		start_angle;
	t_ray_hit	hit;

	game = (t_game *)param;
	fov = M_PI / 3;
	start_angle = game->player.angle - (fov / 2);
	game->img.img = mlx_new_image(game->mlx, game->win_w, game->win_h);
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bpp, &game->img.line_len, &game->img.endian);
	render_background(game);
	x = 0;
	while (x < game->win_w)
	{
		ray_angle = start_angle + ((double)x / game->win_w) * fov;
		hit = cast_ray(game, ray_angle);
		draw_wall_slice(game, x, &hit);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	mlx_destroy_image(game->mlx, game->img.img);
	return (0);
}

int	init_game(t_game *game)
{
	game->win_w = 640;
	game->win_h = 480;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "cub3D");
	if (!game->win)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	char		**files;
	t_map_data	map;
	t_game		game;

	ft_bzero(&map, sizeof(map));
	ft_bzero(&game, sizeof(game));
	if (ac != 2)
		return (1);
	files = open_map(av[1]);
	if (!files)
		return (1);
	if (check_file(files, &map))
		return (1);
	game.color.set_floor = map.colors.set_floor;
	game.color.set_ceiling = map.colors.set_ceiling;
	game.player = map.player;
	game.map = map.map;
	if (!init_game(&game))
		return (1);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop_hook(game.mlx, render_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
