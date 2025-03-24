/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:16:34 by jodiaz-a          #+#    #+#             */
/*   Updated: 2025/02/27 15:30:04 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	flood_fill(t_data *dt, int courrent_pos)
{
	if (courrent_pos < 0 || courrent_pos > (dt->fi->nc * dt->fi->nl))
		return (raise_error("Parsing", "map open 1.", 1, true), 1);
	if (dt->map_verif[courrent_pos] == '1'
		|| dt->map_verif[courrent_pos] == 'x')
		return (1);
	else if (dt->map_verif[courrent_pos] == ' '
		|| dt->map_verif[courrent_pos] == '\n')
		return (raise_error("Parsing", "map open 2.", 1, true), 1);
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
	return (0);
}
