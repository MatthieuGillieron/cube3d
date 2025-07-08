/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_wall.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:06 by mg                #+#    #+#             */
/*   Updated: 2025/07/04 16:15:28 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include <math.h>

static unsigned int	blend_shadow(unsigned int base, double f, double t)
{
	int	br;
	int	bg;
	int	bb;
	int	r;
	int	g;
	int	b;
	// Subtle animated blue tint
	int	blue_tint = (int)(10 + 10 * sin(2 * M_PI * t));
	br = (base >> 16) & 0xFF;
	bg = (base >> 8) & 0xFF;
	bb = base & 0xFF;
	// Shadow: 1.0 at top, 0.5 at bottom
	double shadow = 1.0 - 0.5 * f;
	r = (int)(br * shadow);
	g = (int)(bg * shadow);
	b = (int)(bb * shadow + blue_tint * f);
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;
	if (r < 0) r = 0;
	if (g < 0) g = 0;
	if (b < 0) b = 0;
	return ((r << 16) | (g << 8) | b);
}

static void	draw_wall_column(t_game *game, t_img *texture, t_draw_params *dp)
{
	int			y;
	int			tex_y;
	double		step;
	double		tex_pos;
	char		*dst;
	double		f;
	unsigned int	base_color;
	unsigned int	final_color;
	double		t;

	step = 1.0 * texture->height / dp->line_height;
	tex_pos = (dp->draw_start - game->win_h / 2 + dp->line_height / 2) * step;
	t = fmod(get_time_seconds(), 10.0) / 10.0;
	y = dp->draw_start;
	while (y <= dp->draw_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		dst = game->img.addr
			+ (y * game->img.line_len + dp->x * (game->img.bpp / 8));
		base_color = get_texture_color(texture, dp->tex_x, tex_y);
		f = (dp->line_height > 1) ? (double)(y - dp->draw_start) / (dp->line_height - 1) : 0.0;
		final_color = blend_shadow(base_color, f, t);
		*(unsigned int *)dst = final_color;
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
