/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:16:34 by jodiaz-a          #+#    #+#             */
/*   Updated: 2025/02/06 11:13:22 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	flood_fill(t_data *dt, int courrent_pos)
{
	if (courrent_pos < 0 || courrent_pos > (dt->fi->nc * dt->fi->nl))
		return (raise_error("Error\n", "map open.\n", 1, true), 1);
	if (dt->map_verif[courrent_pos] == '1'
		|| dt->map_verif[courrent_pos] == 'x')
		return (1);
	else if (dt->map_verif[courrent_pos] == ' '
		|| dt->map_verif[courrent_pos] == '\n')
		return (raise_error("Error\n", "map open.\n", 1, true), 1);
	else if (dt->map_verif[courrent_pos] == '0'
		|| dt->map_verif[courrent_pos] == 'N'
		|| dt->map_verif[courrent_pos] == 'E'
		|| dt->map_verif[courrent_pos] == 'W'
		|| dt->map_verif[courrent_pos] == 'S')
		dt->map_verif[courrent_pos] = 'x';
	flood_fill(dt, courrent_pos - dt->fi->nc);
	flood_fill(dt, courrent_pos + dt->fi->nc);
	if (courrent_pos % dt->fi->nc != 0)
		flood_fill(dt, courrent_pos - 1);
	if ((courrent_pos + 1) % dt->fi->nc != 0)
		flood_fill(dt, courrent_pos + 1);
	return (0);
}
