/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:26:24 by tclaereb          #+#    #+#             */
/*   Updated: 2025/02/03 17:43:02 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// printing_all_file_info(&file_info, &dt);
int	main(int ac, char **av)
{
	t_data	dt;
	t_file	file_info;

	if (ac != 2 || !av || !av[1] || !ft_is_cub((const char *)av[1]))
		raise_error("Parsing", "file inexistent or wrong file.", 1, 1);
	init_t_file(&file_info);
	dt.map_verif = NULL;
	dt.fi = &file_info;
	read_file(av[1], &dt);
	str_to_table(&dt);
	raise_error("Perfect", "Program ends well.", 1, 1);
}
