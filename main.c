/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:26:24 by tclaereb          #+#    #+#             */
/*   Updated: 2025/02/07 13:53:30 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	faire en sorte que raise_error/perror close la mlx
	pq je segfault????????
	si tout pres du mur, limite les calculs
	
	J: 
	- DONE: verifier la map bien ferme 
	- DONE: si extension pngg ca devrait etre faux
	- DONE: couleur du ciel et du sol en int * (ne prendre que les premiers 3 chiffres
		separe par une virgule, si il n'y a pas on me zero al la place)
	- DONE: limite de taille pr la map
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

/**
 * A EFFACER
 */
void	printing_all_file_info(t_file *fi, t_data *dt)
{
	printf("\nfi->no: %s\n", fi->no);
	printf("fi->so: %s\n", fi->so);
	printf("fi->we: %s\n", fi->we);
	printf("fi->ea: %s\n", fi->ea);
	printf("fi->f: %i %i %i\n", fi->f[0], fi->f[1], fi->f[2]);
	printf("fi->c: %i %i %i\n", fi->c[0], fi->c[1], fi->c[2]);
	printf("fi->complet: %i\n", fi->complet);
	printf("fi->nl: %i\n", fi->nl);
	printf("fi->nc: %i\n", fi->nc);
	printf("fi->line: %s\n", fi->line);
	printf("fi->valid: %d\n", fi->valid);
	printf("dt->map_verif: \n");
	for (int i = 0; i < (fi->nc * fi->nl); i++)
	{
		if (i % dt->fi->nc == 0 && i != 0)
			printf("\n");
		printf("%c", dt->map_verif[i]);
	}
	printf("\n");
	printf("dt->pos_player: %i\n", dt->pos_player);
	printf("dt->vue_player: %c\n", dt->vue_player);
	printf("char **map:\n");
	for (int i = 0; i < dt->fi->nl ; i++)
	{
		printf("%s\n", dt->map[i]);
	}
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
	printing_all_file_info(&file_info, &dt);
	cub = gb_malloc(sizeof(t_cub));
	cub->player_orientation = dt.vue_player;
	cub->map = dt.map;
	cub->mapX = dt.fi->nc;
	cub->mapY = dt.fi->nl;
	load_texture(cub, &file_info);
	window = create_window(cub);
	mlx_loop(window);
	mlx_terminate(window);
}
