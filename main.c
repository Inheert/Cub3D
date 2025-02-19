/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:26:24 by tclaereb          #+#    #+#             */
/*   Updated: 2025/02/19 09:16:27 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	faire en sorte que raise_error/perror close la mlx
	verifier la map bien ferme
	limite de taille pr la map
	si extension pngg ca devrait etre faux
	couleur du ciel et du sol en int *
	pq je segfault????????
	si tout pres du mur, limite les calculs
*/

void	load_texture(t_cub *cub, t_file *file_info)
{
	mlx_texture_t	*buff;

	buff = mlx_load_png(file_info->no);
	if (!buff)
		raise_perror("A problem occur while loading North texture.", 1);
	cub->north_texture = buff;

	buff = mlx_load_png(file_info->so);
	if (!buff)
		raise_perror("A problem occur while loading South texture.", 1);
	cub->south_texture = buff;

	buff = mlx_load_png(file_info->we);
	if (!buff)
		raise_perror("A problem occur while loading West texture.", 1);
	cub->west_texture = buff;

	buff = mlx_load_png(file_info->ea);
	if (!buff)
		raise_perror("A problem occur while loading East texture.", 1);
	cub->east_texture = buff;
}

int	main(int ac, char **av)
{
	t_data	dt;
	t_file	file_info;
	t_cub	*cub;
	mlx_t	*window;

	if (ac != 2 || !av || !av[1] || !ft_is_cub((const char *)av[1]))
		raise_error("Parsing", "file inexistent or wrong file.", 1, 1);
	init_t_file(&file_info);
	dt.map_verif = NULL;
	dt.fi = &file_info;
	read_file(av[1], &dt);
	str_to_table(&dt);
	cub = gb_malloc(sizeof(t_cub));
	cub->player_orientation = dt.vue_player;
	cub->map = dt.map;
	cub->map_x = dt.fi->nc;
	cub->map_y = dt.fi->nl;
	cub->floor_color = dt.fi->f;
	cub->ceiling_color = dt.fi->c;
	load_texture(cub, &file_info);
	window = create_window(cub);
	mlx_loop(window);
	mlx_terminate(window);
}
