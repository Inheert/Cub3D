/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:25:51 by tclaereb          #+#    #+#             */
/*   Updated: 2024/12/10 13:32:58 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rectangle(uint32_t x, uint32_t y, int width, int height, uint32_t color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
			mlx_put_pixel(g_game_container, x + j, y + i, color);
	}
}

uint32_t	get_hexa_color(unsigned int r, unsigned int g, unsigned int b, unsigned int alpha)
{
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (alpha > 255)
		alpha = 255;
	return ((r << 24) | (g << 16) | (b << 8) | alpha);
}

uint32_t	get_color(char symbol)
{
	if (symbol == '0' || symbol == 'P')
		return (get_hexa_color(255, 0, 0, 255));
	else if (symbol == '1')
		return(get_hexa_color(0, 255, 0, 255));
	return (get_hexa_color(0, 0, 0, 255));
}

void	draw_map(t_map **map)
{
	int					slot_width;
	int					slot_height;
	unsigned int		i;
	unsigned int		j;

	slot_width = W_WIDTH * 0.5  / (*map)->line_count;
	slot_height = W_HEIGHT / (*map)->col_count;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (++j < (*map)->col_count)
		{
			draw_rectangle(slot_width * j, slot_height * i, slot_width, slot_height, get_color(map[i][j].slot));
		}
	}
}
