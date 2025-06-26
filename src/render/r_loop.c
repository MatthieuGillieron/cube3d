/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_loop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:53 by mg                #+#    #+#             */
/*   Updated: 2025/06/26 15:53:30 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

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
