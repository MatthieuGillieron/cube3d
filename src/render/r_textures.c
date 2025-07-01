/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_textures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:09:38 by maximemarti       #+#    #+#             */
/*   Updated: 2025/07/01 14:45:49 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

t_img	*get_wall_texture(t_game *game,
	t_ray_hit *hit, double ray_angle)
{
	while (ray_angle < 0)
		ray_angle += 2 * M_PI;
	while (ray_angle >= 2 * M_PI)
		ray_angle -= 2 * M_PI;
	if (hit->side == 0)
	{
		if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
			return (&game->textures.west);
		else
			return (&game->textures.east);
	}
	else
	{
		if (ray_angle > 0 && ray_angle < M_PI)
			return (&game->textures.south);
		else
			return (&game->textures.north);
	}
}

int	get_texture_color(t_img *texture, int x, int y)
{
	char	*dst;
	int		color;

	if (!texture || !texture->addr)
		return (0);
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	dst = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}
