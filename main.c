/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:26:24 by tclaereb          #+#    #+#             */
/*   Updated: 2024/12/05 13:50:14 by jodiaz-a         ###   ########.fr       */
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
	fi->lb = NULL;
	fi->lm = NULL;
	fi->la = NULL;

	fi->valid = true;
	
}

int	main(int ac, char **av)
{
	t_data	dt;
	t_file	file_info;

	if (ac != 2 || !av || !av[1] || !ft_is_cub((const char *)av[1]))
		raise_error("Parsing", "file inexistent or wrong file.", 1 ,1);
	init_t_file(&file_info);
	dt.fi = &file_info;
	read_file(av[1], &dt);
}
