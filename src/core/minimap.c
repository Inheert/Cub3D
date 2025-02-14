/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 08:59:16 by tclaereb          #+#    #+#             */
/*   Updated: 2025/02/14 06:05:51 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	real_draw_map_2d(t_cub *cub, int map_x, int map_y, int pos[2])
{
	if (map_x < 0 || map_y < 0 || map_x >= cub->map_x || map_y >= cub->map_y)
		draw_rectangle(create_param_struct(pos[0] * MINIMAP_CELL_SIZE + 1,
				pos[1] * MINIMAP_CELL_SIZE + 1, MINIMAP_CELL_SIZE - 1,
				MINIMAP_CELL_SIZE - 1), get_hexa_color(41, 79, 73, 255),
			cub->game_img);
	else if (cub->map[map_y][map_x] == '1')
		draw_rectangle(create_param_struct(pos[0] * MINIMAP_CELL_SIZE + 1,
				pos[1] * MINIMAP_CELL_SIZE + 1, MINIMAP_CELL_SIZE - 1,
				MINIMAP_CELL_SIZE - 1), get_hexa_color(129, 120, 145, 255),
			cub->game_img);
	else
		draw_rectangle(create_param_struct(pos[0] * MINIMAP_CELL_SIZE + 1,
				pos[1] * MINIMAP_CELL_SIZE + 1, MINIMAP_CELL_SIZE - 1,
				MINIMAP_CELL_SIZE - 1), get_hexa_color(179, 168, 175, 255),
			cub->game_img);
}

void	draw_map_2d(t_cub *cub, int x, int y)
{
	int	cell_count;
	int	start_x;
	int	start_y;
	int	pos[2];

	cell_count = MINIMAP_SIZE / MINIMAP_CELL_SIZE;
	start_x = (int)(cub->player_pos[0] / TILE_SIZE) - cell_count * 0.5;
	start_y = (int)(cub->player_pos[1] / TILE_SIZE) - cell_count * 0.5;
	draw_rectangle(create_param_struct(0, 0, MINIMAP_SIZE - cell_count * 0.5,
			MINIMAP_SIZE - cell_count * 0.5), get_hexa_color(42, 42, 42, 255),
		cub->game_img);
	y = -1;
	while (++y < cell_count)
	{
		x = -1;
		while (++x < cell_count)
		{
			pos[0] = x;
			pos[1] = y;
			real_draw_map_2d(cub, start_x + x, start_y + y, pos);
		}
	}
	draw_rectangle(create_param_struct(MINIMAP_SIZE * 0.5,
			MINIMAP_SIZE * 0.5, 15, 15), get_hexa_color(0, 0, 0, 255),
		cub->game_img);
}
