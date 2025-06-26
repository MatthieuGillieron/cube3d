/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:15:08 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/26 15:40:08 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

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
