/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_wall.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:06 by mg                #+#    #+#             */
/*   Updated: 2025/07/02 09:03:01 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	draw_wall_column(t_game *game, t_img *texture, t_draw_params *dp)
{
	int		y;
	int		tex_y;
	double	step;
	double	tex_pos;
	char	*dst;

	step = 1.0 * texture->height / dp->line_height;
	tex_pos = (dp->draw_start - game->win_h / 2 + dp->line_height / 2) * step;
	y = dp->draw_start;
	while (y <= dp->draw_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		dst = game->img.addr
			+ (y * game->img.line_len + dp->x * (game->img.bpp / 8));
		*(unsigned int *)dst = get_texture_color(texture, dp->tex_x, tex_y);
		y++;
	}
}

static int	calc_tex_x(t_ray_hit *hit, t_img *texture, double ray_angle)
{
	int	tex_x;

	tex_x = (int)(hit->wall_x * texture->width);
	if ((hit->side == 0 && ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
		|| (hit->side == 1 && ray_angle > 0 && ray_angle < M_PI))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

static int	calc_draw_start(int line_height, int win_h)
{
	int	draw_start;

	draw_start = -line_height / 2 + win_h / 2;
	if (draw_start < 0)
		draw_start = 0;
	return (draw_start);
}

static int	calc_draw_end(int line_height, int win_h)
{
	int	draw_end;

	draw_end = line_height / 2 + win_h / 2;
	if (draw_end >= win_h)
		draw_end = win_h - 1;
	return (draw_end);
}

void	draw_wall_slice(t_game *game, int x, t_ray_hit *hit, double ray_angle)
{
	t_img			*texture;
	int				tex_x;
	t_draw_params	dp;

	if (hit->distance <= 0)
		hit->distance = 0.1;
	texture = get_wall_texture(game, hit, ray_angle);
	if (!texture || !texture->addr)
		return ;
	dp.line_height = (int)(game->win_h / hit->distance);
	dp.draw_start = calc_draw_start(dp.line_height, game->win_h);
	dp.draw_end = calc_draw_end(dp.line_height, game->win_h);
	tex_x = calc_tex_x(hit, texture, ray_angle);
	dp.x = x;
	dp.tex_x = tex_x;
	draw_wall_column(game, texture, &dp);
}
