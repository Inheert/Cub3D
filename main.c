/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:26:24 by tclaereb          #+#    #+#             */
/*   Updated: 2024/12/04 12:43:16 by jodiaz-a         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	// t_data dt;
	// t_file file_info;

	if (ac != 2 || !av || !av[1] || !ft_is_cub((const char *)av[1]))
		return (printf("Error: File inexistent or wrong file.\n"), 2);
	// if (read_file(av[1], &dt) == NULL)
	// 	return (printf("Error: Map invalid.\n"), 2);
}
