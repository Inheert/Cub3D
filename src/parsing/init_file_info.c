/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:46:57 by jodiaz-a          #+#    #+#             */
/*   Updated: 2025/02/19 08:11:10 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Get organize the information in the t_file structure
 */
bool	init_file_info(char *line, t_data *dt)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		return (dt->fi->no = take_path_info(line), true);
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (dt->fi->so = take_path_info(line), true);
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (dt->fi->we = take_path_info(line), true);
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (dt->fi->ea = take_path_info(line), true);
	else if (ft_strncmp(line, "F", 1) == 0)
		return (dt->fi->f = take_colors(line), true);
	else if (ft_strncmp(line, "C", 1) == 0)
		return (dt->fi->c = take_colors(line), true);
	return (false);
}

bool	free_and_return(char *line, char *line1, bool result)
{
	if (line)
		gb_free(line);
	if (line1)
		gb_free(line1);
	return (result);
}

int	is_player(char *p, t_data *dt, int i)
{
	static int	player = 0;

	if (player == 0 && (*p == 'E' || *p == 'W' || *p == 'N' || *p == 'S'))
		return (player++, dt->pos_player = i, dt->vue_player = *p, 1);
	else if ((*p == 'E' || *p == 'W' || *p == 'N' || *p == 'S'))
		return (dt->fi->valid = false, 2);
	if (*p == '1' || *p == '0' || *p == ' ' || *p == '\n')
		return (1);
	return (dt->fi->valid = false, 2);
}
