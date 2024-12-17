/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:26:24 by tclaereb          #+#    #+#             */
/*   Updated: 2024/12/14 09:49:31 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Make sure the file pas as argument is type .cub
 */
int	ft_is_cub(const char *file)
{
	char	*p;

	p = NULL;
	if (file == NULL)
		return (0);
	if ((p = ft_strchr(file, '.')) == NULL)
		return (0);
	if (ft_strncmp(".cub", p, 4) != 0)
		return (0);
	return (1);
}

mlx_t		*g_window = NULL;
mlx_image_t	*g_game_container = NULL;

int	main(int argc, char **argv)
{
	// t_data dt;
	// t_file file_info;
	// if (ac != 2 || !av || !av[1] || !ft_is_cub((const char *)av[1]))
	// 	raise_error("Parsing", "file inexistent or wrong file.", 1 ,1);
	// if (read_file(av[1], &dt) == NULL)
	// 	return (printf("Error: Map invalid.\n"), 2);
	(void)argc; (void)argv;

	char	**old_map;

	old_map = gb_malloc((7 + 1) * sizeof(char *));
	old_map[5] = NULL;
	old_map[0] = gb_malloc(7 * sizeof(char));
	old_map[0] = "11111\0";
	old_map[1] = gb_malloc(7 * sizeof(char));
	old_map[1] = "10001\0";
	old_map[2] = gb_malloc(7 * sizeof(char));
	old_map[2] = "10P01\0";
	old_map[3] = gb_malloc(7 * sizeof(char));
	old_map[3] = "10001\0";
	old_map[4] = gb_malloc(7 * sizeof(char));
	old_map[4] = "11111\0";

	mlx_t	*window;

	t_map	**map;
	map = t_map_create(old_map);
	printf("wefone\n");
	printf("%x\n", (255 << 24) | (0 << 16) | (0 << 8) | 255);
	// return (0);
	window = create_window(map);
	player_init();
	mlx_loop(window);
	mlx_terminate(window);
}
