/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_loop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:53 by mg                #+#    #+#             */
/*   Updated: 2025/07/04 15:54:37 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include <sys/time.h>

void	update_open_doors(t_game *game, double now)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < game->open_door_count)
	{
		if (now - game->open_doors[i].open_time >= 3.0)
		{
			x = game->open_doors[i].x;
			y = game->open_doors[i].y;
			if (game->map[y][x] == '0')
				game->map[y][x] = 'D';
			j = i;
			while (j < game->open_door_count - 1)
			{
				game->open_doors[j] = game->open_doors[j + 1];
				j++;
			}
			game->open_door_count--;
		}
		else
			i++;
	}
}

void	render_rays(t_game *game, double start_angle)
{
	int			x;
	double		ray_angle;
	t_ray_hit	hit;

	x = 0;
	while (x < game->win_w)
	{
		ray_angle = start_angle + ((double)x / game->win_w) * FOV;
		hit = cast_ray(game, ray_angle);
		draw_wall_slice(game, x, &hit, ray_angle);
		x++;
	}
}

int	render_loop(void *param)
{
	t_game	*game;
	double	start_angle;

	game = (t_game *)param;
	update_movement(game);
	update_open_doors(game, get_time_seconds());
	start_angle = game->player.angle - (FOV / 2);
	game->img.img = mlx_new_image(game->mlx, game->win_w, game->win_h);
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bpp, &game->img.line_len, &game->img.endian);
	render_background(game);
	render_rays(game, start_angle);
	render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	mlx_destroy_image(game->mlx, game->img.img);
	return (0);
}
