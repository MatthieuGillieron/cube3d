/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_textures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:35:38 by mg                #+#    #+#             */
/*   Updated: 2025/06/29 10:00:25 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static char	*trim_path(char *path)
{
	char	*trimmed_path;

	if (!path)
		return (NULL);
	trimmed_path = ft_strtrim(path, " \t\n");
	return (trimmed_path);
}

static int	load_single_texture(t_game *game, t_img *texture, char *path)
{
	char	*trimmed_path;

	trimmed_path = trim_path(path);
	if (!trimmed_path)
		return (0);
	texture->img = mlx_xpm_file_to_image(game->mlx, trimmed_path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Failed to load texture: %s\n", trimmed_path);
		free(trimmed_path);
		return (0);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
	if (!texture->addr)
	{
		printf("Failed to get texture data: %s\n", trimmed_path);
		mlx_destroy_image(game->mlx, texture->img);
		free(trimmed_path);
		return (0);
	}
	free(trimmed_path);
	return (1);
}

int	load_textures(t_game *game)
{
	printf("Loading textures...\n");
	printf("NO: %s\n", game->map_data.textures.no);
	printf("SO: %s\n", game->map_data.textures.so);
	printf("EA: %s\n", game->map_data.textures.ea);
	printf("WE: %s\n", game->map_data.textures.we);
	if (!load_single_texture(game, &game->textures.north, \
		game->map_data.textures.no))
		return (0);
	if (!load_single_texture(game, &game->textures.south, \
		game->map_data.textures.so))
		return (0);
	if (!load_single_texture(game, &game->textures.east, \
		game->map_data.textures.ea))
		return (0);
	if (!load_single_texture(game, &game->textures.west, \
		game->map_data.textures.we))
		return (0);
	printf("All textures loaded successfully!\n");
	return (1);
}
