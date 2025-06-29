/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_check_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:45:11 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/29 16:20:30 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	check_extension(const char *path)
{
	const char	*ext;

	ext = ft_strrchr(path, '.');
	if (!ext || ft_strncmp(ext, ".xpm", 5) != 0)
	{
		write(2, "Error\nInvalid texture extension\n", 33);
		return (0);
	}
	return (1);
}

static int	try_load_image(const char *path, void *mlx)
{
	void	*img;
	int		w;
	int		h;

	img = mlx_xpm_file_to_image(mlx, (char *)path, &w, &h);
	if (!img)
	{
		write(2, "Error\nFailed to load texture\n", 30);
		return (0);
	}
	mlx_destroy_image(mlx, img);
	return (1);
}

int	is_valid_texture(const char *path, void *mlx)
{
	int		fd;
	char	*new_path;
	int		result;

	new_path = ft_strtrim(path, " \t\n");
	fd = open(new_path, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\nCannot open texture file\n", 32);
		free(new_path);
		return (0);
	}
	close(fd);
	if (!check_extension(new_path))
	{
		free(new_path);
		return (0);
	}
	result = try_load_image(new_path, mlx);
	free(new_path);
	return (result);
}

int	check_path(t_map_data *data, void *mlx_ptr)
{
	if (!is_valid_texture(data->textures.no, mlx_ptr))
		return (0);
	if (!is_valid_texture(data->textures.so, mlx_ptr))
		return (0);
	if (!is_valid_texture(data->textures.we, mlx_ptr))
		return (0);
	if (!is_valid_texture(data->textures.ea, mlx_ptr))
		return (0);
	return (1);
}

int	check_file(char **files, t_map_data *map)
{
	void	*mlx;

	if (!split_sections(files, map))
	{
		printf("Error\nInvalid map format.\n");
		free_map_data(map);
		return (1);
	}
	if (!is_map_enclosed(map->map, &map->player))
	{
		printf("Map not good\n");
		return (1);
	}
	mlx = mlx_init();
	if (!check_path(map, mlx))
	{
		printf("Error\nInvalid texture paths.\n");
		free_map_data(map);
		free(files);
		return (1);
	}
	parse_colors(map);
	assign_direction(&map->player);
	return (0);
}
