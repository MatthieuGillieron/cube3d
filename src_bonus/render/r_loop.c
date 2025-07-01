/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_loop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:53 by mg                #+#    #+#             */
/*   Updated: 2025/07/01 11:08:07 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	render_loop(void *param)
{
	t_game		*game;
	int			x;
	double		start_angle;
	double		ray_angle;
	t_ray_hit	hit;

	game = (t_game *)param;
	update_movement(game);
	start_angle = game->player.angle - (FOV / 2);
	game->img.img = mlx_new_image(game->mlx, game->win_w, game->win_h);
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bpp, &game->img.line_len, &game->img.endian);
	render_background(game);
	x = 0;
	while (x < game->win_w)
	{
		ray_angle = start_angle + ((double)x / game->win_w) * FOV;
		hit = cast_ray(game, ray_angle);
		draw_wall_slice(game, x, &hit, ray_angle);
		x++;
	}
	render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	mlx_destroy_image(game->mlx, game->img.img);
	return (0);
}
