/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:15:08 by maximemarti       #+#    #+#             */
/*   Updated: 2025/06/24 00:16:14 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	print_texture(t_texture *tex)
{
	printf("Textures:\n");
	printf("  NO: %s\n", tex->no);
	printf("  SO: %s\n", tex->so);
	printf("  WE: %s\n", tex->we);
	printf("  EA: %s\n", tex->ea);
}

void	print_color(t_color *col)
{
	printf("Colors:\n");
	printf("  Floor: %s\n", col->floor);
	printf("  Ceiling: %s\n", col->ceiling);
}

void	print_colors_int(t_colors_int *ci)
{
	printf("Colors (int):\n");
	printf("  Floor: %d\n", ci->floor);
	printf("  Ceiling: %d\n", ci->ceiling);
	printf("  Floor set: %d\n", ci->floor_set);
	printf("  Ceiling set: %d\n", ci->ceiling_set);
}

void	print_map(char **map)
{
	printf("Map:\n");
	if (!map)
	{
		printf("  (null)\n");
		return ;
	}
	for (int i = 0; map[i]; i++)
	{
		printf("  %s\n", map[i]);
	}
}

void	print_map_data(t_map_data *data)
{
	printf("=== Map Data ===\n");
	print_texture(&data->textures);
	print_color(&data->colors);
	print_colors_int(&data->colors_int);
	print_map(data->map);
}

void	print_player(t_player *player)
{
	printf("Player:\n");
	printf("  X: %d\n", player->x);
	printf("  Y: %d\n", player->y);
	printf("  Direction: %c\n", player->direction);
}

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
	parse_color(&map, 1);
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
