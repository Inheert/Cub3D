/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:16:34 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/12/04 16:17:10 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * a tester at a nettoyer
 */
int	flood_fill(t_data *dt, int courrent_pos)
{
	if (courrent_pos < 0 || courrent_pos > (dt->fi->nc * dt->fi->nl))
		return (perror("Map open"), free(dt->map_verif), exit(EXIT_FAILURE), 1);// on sort completement du program
	if (dt->map_verif[courrent_pos] == '1'
		|| dt->map_verif[courrent_pos] == 'x')
		return (1);
	else if (dt->map[courrent_pos] == ' '
		|| dt->map[courrent_pos] == '\n')
		return (1);
	else if (dt->map_verif[courrent_pos] == '0'
		|| dt->map_verif[courrent_pos] == 'N'
		|| dt->map_verif[courrent_pos] == 'E'
		|| dt->map_verif[courrent_pos] == 'W'
		|| dt->map_verif[courrent_pos] == 'S')
		dt->map_verif[courrent_pos] = 'x';
	flood_fill(dt, courrent_pos - dt->fi->nc);
	flood_fill(dt, courrent_pos + dt->fi->nc);
	flood_fill(dt, courrent_pos - 1);
	flood_fill(dt, courrent_pos + 1);
	return (0)
}
