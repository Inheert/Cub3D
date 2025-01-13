/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:26:24 by tclaereb          #+#    #+#             */
/*   Updated: 2024/12/17 13:14:39 by jodiaz-a         ###   ########.fr       */
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
	
}

int	main(int ac, char **av)
{
	t_data	dt;
	t_file	file_info;

	if (ac != 2 || !av || !av[1] || !ft_is_cub((const char *)av[1]))
		raise_error("Parsing", "file inexistent or wrong file.", 1 ,1);
	init_t_file(&file_info);
	dt.map_verif = NULL;
	dt.fi = &file_info;
	read_file(av[1], &dt);
	printing_all_file_info(&file_info, &dt);
	
	raise_error("Perfect", "Program ends well.", 1 ,1);//ne
}
