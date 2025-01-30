/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:26:24 by tclaereb          #+#    #+#             */
/*   Updated: 2025/01/30 09:59:22 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Definir une image pr le jeu
	Definir une image pr la minimap
	Garder un TILE-SIZE fixe tout en faisant en sorte que les images s'adaptent a la taille de l'ecran
*/

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

void	init_t_file(t_file *fi)
{
	fi->no = NULL;
	fi->so = NULL;
	fi->we = NULL;
	fi->ea = NULL;
	fi->f = NULL;
	fi->c = NULL;
	fi->complet = 1;

	fi->nl = 0;
	fi->nc = 0;

	fi->line = NULL;

	fi->valid = true;

}

void	printing_all_file_info(t_file *fi, t_data *dt)
{
	printf("\nfi->no: %s\n", fi->no);
	printf("fi->so: %s\n", fi->so);
	printf("fi->we: %s\n", fi->we);
	printf("fi->ea: %s\n", fi->ea);
	printf("fi->f: %s\n", fi->f);
	printf("fi->c: %s\n", fi->c);
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

void str_to_table(t_data *dt)
{

	int		i;
	int		j;
	int		k;

	dt->map = (char **)gb_malloc(sizeof(char *) * dt->fi->nl);
	if (!dt->map)
		return;
	k = 0;
	i = 0;
	while (i < dt->fi->nl)
	{
		dt->map[i] = (char *)gb_malloc(sizeof(char) * (dt->fi->nc + 1));
		if (!dt->map)
			return;
		j = 0;
		while (j < dt->fi->nc)
		{
			if (dt->pos_player == k)
			{
				dt->map[i][j] = dt->vue_player;
				k++;
			}
			else
				dt->map[i][j] = dt->map_verif[k++];
			j++;
		}
		dt->map[i][j] = '\0';
		i++;
	}
}

void	load_texture(t_cub *cub, t_file *file_info)
{
	mlx_texture_t	*buff;
	(void)cub;
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
		raise_error("Parsing", "file inexistent or wrong file.", 1 ,1);
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
	raise_error("Perfect", "Program ends well.", 1 ,1);//ne
}
