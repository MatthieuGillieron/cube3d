/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:15:08 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/24 08:44:31 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

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
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\nCannot open texture file\n", 32);
		return (0);
	}
	close(fd);
	if (!check_extension(path))
		return (0);
	return (try_load_image(path, mlx));
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

int	check_file(char **files, t_map_data	map)
{
	//void	*mlx;

	if (!split_sections(files, &map))
	{
		printf("Error\nInvalid map format.\n");
		free_map_data(&map);
		free(files);
		return (1);
	}
	if (!is_map_enclosed(map.map, &map.player))
	{
		printf("Map not good\n");
		return (1);
	}
	//mlx = mlx_init();
	/*if (!check_path(&map, mlx))
	{
		printf("Error\nInvalid texture paths.\n");
		free_map_data(&map);
		free(files);
		return (1);
	}*/
	parse_colors(&map);
	print_map_data(&map);
	print_player(&map.player);
	return (0);
}

int	main(int ac, char **av)
{
	char		**files;
	t_map_data	map = {0};

	if (ac != 2)
		return (1);
	files = open_map(av[1]);
	if (!check_file(files, map))
		return (1);
	return (0);
}
